#include "lib/decoder.h"
#include "lib/encoder.h"

#include <stdio.h>
#ifdef _WIN32
    #include <fcntl.h>
    #include <io.h>
#endif

/* --- MAIN --- */
int main(void) {

    #ifdef _WIN32
        // Переключаем stdin и stdout в бинарный режим в Windows
        _setmode(_fileno(stdin), _O_BINARY);
        _setmode(_fileno(stdout), _O_BINARY);
    #endif

    const char mode = (char) getchar();
    if (mode == 'c') {
        encode();
    } else {
        decode();
    }

    return EXIT_SUCCESS;
}