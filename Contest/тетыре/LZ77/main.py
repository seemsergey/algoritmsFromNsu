#!/usr/bin/env python3
# stress_test_lz77_fixed.py
# Версия, адаптированная под scanf("%s") в твоём C-коде

import os
import sys
import random
import subprocess
import re
import signal

EXECUTABLE = "./lz77_encoder.exe"
MAX_TESTS = 1000
SAVE_FAILS = True

stats = {"passed": 0, "failed": 0, "total": 0}


def signal_handler(sig, frame):
    print(f"\n⚠️ Прервано. {stats['passed']} OK, {stats['failed']} FAIL из {stats['total']}")
    sys.exit(130)


signal.signal(signal.SIGINT, signal_handler)


# ===================== ДЕКОДЕР =====================

def decode_lz77(tokens, expected_len):
    buf = []
    for offset, length, ch in tokens:
        for _ in range(length):
            if offset == 0 or offset > len(buf):
                return None
            buf.append(buf[-offset])
        if ch != '\\0':
            buf.append(ch)
    res = ''.join(buf)
    return res if len(res) == expected_len else None


# ===================== ПАРСЕР =====================

pattern = re.compile(r'^\((\d+),(\d+),(\\0|.)\)$')

def parse_output(lines):
    tokens = []
    for i, line in enumerate(lines, 1):
        line = line.strip()
        if not line:
            continue
        m = pattern.match(line)
        if not m:
            return None, f"Строка {i}: неверный формат '{line}'"
        tokens.append((int(m.group(1)), int(m.group(2)), m.group(3)))
    return tokens, None


# ===================== ГЕНЕРАЦИЯ СТРОК =====================

# Только символы без пробелов!
ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

def gen_string(n):
    return ''.join(random.choice(ALPHABET) for _ in range(n))


def generate_test_case(test_id):
    MAX_WB = 1000
    MAX_LEN = 10000

    window = random.randint(1, MAX_WB)
    buffer = random.randint(1, MAX_WB)

    # разные типы строк
    t = random.choice(["random", "repeat", "pattern"])

    if t == "random":
        s = gen_string(random.randint(1, MAX_LEN))

    elif t == "repeat":
        base = gen_string(random.randint(1, 20))
        s = (base * random.randint(5, 500))[:MAX_LEN]

    else:
        s = ""
        for _ in range(random.randint(10, 200)):
            if random.random() < 0.4 and s:
                start = random.randint(0, len(s) - 1)
                end = random.randint(start + 1, len(s))
                s += s[start:end]
            else:
                s += gen_string(random.randint(1, 2000))
            s = s[:MAX_LEN]

    return window, buffer, s


# ===================== ЗАПУСК ПРОГРАММЫ =====================

def run_encoder(w, b, s):
    inp = f"{w} {b}\n{s}\n"
    try:
        r = subprocess.run(
            [EXECUTABLE],
            input=inp,
            capture_output=True,
            text=True,
            timeout=3
        )
        out = r.stdout.strip().split('\n') if r.stdout.strip() else []
        return out, r.returncode, r.stderr
    except subprocess.TimeoutExpired:
        return None, -1, "Timeout"


# ===================== ВАЛИДАЦИЯ =====================

def validate(window, buffer, s, lines):
    tokens, err = parse_output(lines)
    if err:
        return False, err

    pos = 0
    for i, (offset, length, ch) in enumerate(tokens):
        if offset > window:
            return False, f"offset>{window}"
        if length > buffer:
            return False, f"length>{buffer}"
        if offset > pos:
            return False, f"ссылка вперёд"
        pos += length + (0 if ch == '\\0' else 1)

    if pos != len(s):
        return False, f"длина не совпадает {pos}!={len(s)}"

    dec = decode_lz77(tokens, len(s))
    if dec != s:
        return False, "декод не совпадает"

    return True, None


# ===================== MAIN =====================

def main():
    if not os.path.isfile(EXECUTABLE):
        print("❌ Нет бинарника")
        sys.exit(1)

    print("🚀 Стресс-тест LZ77\n")

    for test_id in range(MAX_TESTS):
        stats["total"] = test_id + 1

        w, b, s = generate_test_case(test_id)
        out, code, err = run_encoder(w, b, s)

        if code != 0:
            stats["failed"] += 1
            print(f"❌ {test_id}: код возврата {code}")
            continue

        ok, e = validate(w, b, s, out)

        if ok:
            stats["passed"] += 1
        else:
            stats["failed"] += 1
            print(f"\n❌ Тест {test_id}: {e}")
            print("window:", w, "buffer:", b)
            print("input:", s[:200])
            print("output:", out[:10])
            sys.exit(1)

    print(f"\n📊 Итог: {stats['passed']}/{MAX_TESTS}")
    if stats["failed"] == 0:
        print("🎉 Всё прошло!")
    else:
        print("Есть ошибки")


if __name__ == "__main__":
    main()