//
// Created by timo on 28.01.24.
//
#include <stdbool.h>
#include <stdio.h>
#include "minimax.h"
#include "schach.h"


LIST* unsere_nachfolgezustandsfunktion(ZUSTAND z, int player) {
    BRETT* b = (BRETT*) z;
    return schach_nachfolgezustaende(b, player);
}

int unsere_zustandsbewertungsfunktion(ZUSTAND z, int player) {
    BRETT* b = (BRETT*) z;
    return schach_zustandsbewertung(b, player);
}

int main() {
    int TIEFE = 0;
    BRETT* brett = brett_cpy(&einfaches_brett);
    printf("Spielanfang:\n");
    print_brett(brett);
    int player = WHITE;
    bool matt = schach_matt(brett, BLACK);
    while (!matt) {
        printf("%s ist am Zug.\n", (player == WHITE ? "Weiß" : "Schwarz"));
        brett = (BRETT*) minimax((ZUSTAND) brett, TIEFE, player, &unsere_nachfolgezustandsfunktion, &unsere_zustandsbewertungsfunktion);
        print_brett(brett);
        player = schach_next_player(player);
        matt = schach_matt(brett, player);
    }
    printf("schach matt. %s hat gewonnen.\n", (-player == WHITE ? "Weiß" : "Schwarz"));
}
