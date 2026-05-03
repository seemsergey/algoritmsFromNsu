//
// Created by SeemS on 11.10.2025.
//


//существует коллизия имён т.е. не может быть ещё enum с BLUE/RED/GREEN
typedef enum EColor {
    BLUE = 23456,
    RED, // 1
    GREEN // 2
} EColor;

EColor color = RED;