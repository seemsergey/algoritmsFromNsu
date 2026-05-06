cmake_minimum_required(VERSION 4.0)
project(NSU_course)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        "Contest/first/candysmap.c"
        "About types/Structs/Teorhy.c"
        "About types/uniouns/Teorhy.c"
        "About types/enums/Teorhy.c"
        "About types/Lists/Teorhy.c"
        "About types/Lists/Theorhy2.c"
        "About types/Lists/Theory2.c"
        "About types/Stak/StackOnList.c"
        "About types/Stak/Queue.c"
        "About types/Stak/TaskAbout/CorrectSkobochka.c"
        "About types/Stak/TaskAbout/QueueWithPriority.c"
        "About types/Stak/QueueOnStack.c"
        "About types/Stak/TaskAbout/FibonachiOnStack.c"
        "About types/Trees/Theory.c"
        "About types/Trees/обзоды/down.c"
        "About types/Trees/обзоды/DownRecurtion.c"
        "About types/Trees/обзоды/Width.c"
        "About types/Trees/Tasks/BST_YesOrNo.c"
        "About types/Trees/Дерево сумм/Theory.c"
        "About types/Куча/heap.c"
        "About types/DSU/DSU.c"
        "About types/DSU/tasks/1.c"
        "About types/Bloom filter.c"
        "About types/HashMap/HashMap.c"
        "About types/HashMap/struct.c"
        "About types/HashMap/struct.h"
        "About types/HashMap/task/task1.c"
        "About types/HashMap/task/task2.c"
        "functions/Dynamic programming/fiboncahi/main.c"
        "functions/Dynamic programming/tips.c"
        "functions/Dynamic programming/lagushka.c"
        "functions/Dynamic programming/расстояние Левенштейна/main.c"
        "Contest/тетыре/Adaptive delta-coding/ADC.cpp"
        "Contest/тетыре/Adaptive delta-coding/ADC.c"
        "Contest/тетыре/Damerau-Levenshtein distance/DLS.c"
        "About types/граф/main.c"
        "About types/граф/поиск merge base/SMB.c"
        "About types/Trees/RBTree.c"
        "About types/граф/задачка/main.c"
        "About types/граф/топологическая сортировка/main.c"
        "Contest/fifthcoma/gentree/mainVer1prealphademobuid.c"
        Contest/fifthcoma/gentree/main2PreAlphaDemoBuild.c
        "Contest/пятый/Квадрат графа/main.c"
        Contest/пятый/CSR/main.c
        Contest/пятый/virus/main.c
        "About types/граф/Остовной граф(дерево)/main.c"
        "Contest/пятый/Dependency graph/main.c"
        temp.c
        "Contest/пятый/Критический путь проекта/main.c"
        "About types/граф/Алгоритм Форда-Беллмана/через матрицк/deskedition.c"
        "About types/граф/слеш тп ртп/mainfurer.c"
        "Contest/SIXsevenContest/Избыточные кабели/main.c"
        lib/CSR/csr.c
        lib/CSR/csr.h
        "lib/Algoritm Bellman Ford/bellmanFord.h"
        "lib/Algoritm Bellman Ford/bellmanFord.c"
        Contest/SIXsevenContest/Арбитраж/18+/main.c
        Contest/ClassContest7/main.c
        Contest/SIXsevenContest/Арбитраж/main.c
        "Contest/SIXsevenContest/Место встречи/main.c"
        "Contest/SIXsevenContest/Улучшение сети/main.c"
        "About types/граф/алгоритм Флойда–Уоршелла/main.c"
        "Contest/SIXsevenContest/Конденсация графа/main.c"
        "About types/граф/пропускная спосбоность/main.c"
)
