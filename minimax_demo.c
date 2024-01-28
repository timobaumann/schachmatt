//
// Created by timo on 28.01.24.
//
#include <stdbool.h>
#include <stdio.h>
//#include "list.h"
#include "schach.h"
//#include "minimax.h"

int main() {
    BRETT* brett = brett_cpy(*triviales_brett);
    printf("Spielanfang:\n");
    print_brett(brett);
    int player = WHITE;
    bool matt = schach_matt(brett, player);
    while (!matt) {
        printf("%s ist am Zug.\n", (player == WHITE ? "Weiß" : "Schwarz"));
        print_brett(brett);
        matt = schach_matt(brett, player);
    }
    printf("schach matt. %s hat gewonnen.\n", (player == WHITE ? "Weiß" : "Schwarz"));
}