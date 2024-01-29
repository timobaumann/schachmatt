//
// Created by Anja Klosterhuber on 22.01.24.
//
#include <stdlib.h>
#include "schach.h"
#include <stdbool.h>
#include "list.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

void print_brett(void* schachbrett_pointer);

void initialisieren(BRETT schachbrett) {
    memcpy(schachbrett, initiales_brett, sizeof(BRETT));
}

BRETT* brett_cpy(BRETT* in) {
    BRETT* out = calloc(1, sizeof(BRETT));
    memcpy(out, in, sizeof(BRETT));
    return out;
}

int brett_cmp(void* a, void* b) {
    BRETT* brett_a = (BRETT*) a;
    BRETT* brett_b = (BRETT*) b;
    for (int x = 0; x < GROESSE; x++) {
        for (int y = 0; y < GROESSE; y++) {
            int diff = (*brett_a)[x][y] - (*brett_b)[x][y];
            if (diff != 0)
                return diff;
        }
    }
    return 0;
}

bool brett_eql(void* a, void* b) {
    return (bool) brett_cmp(a, b);
}

bool checkoutofbounds(int x, int y) {
    return x >= GROESSE || y >= GROESSE || x < 0 || y < 0;
}

int schach_next_player(int player) {
    return -1 * player;
}


zuege_der_figur* figuren_regeln[7] = {
        [1] = &bauernzuege,
        [2] = &laeuferzuege,
        [3] = &springerzuege,
        [4] = &turmzuege,
        [5] = &damenzuege,
        [6] = &koenigszuege
};

LIST* schach_nachfolgezustaende(BRETT* schachbrett, int player) {
    LIST* folgezustaende = list_new();
    for (int y= 0; y < GROESSE; y++) {
        for (int x = 0; x < GROESSE; x++) {
            int aktuelle_figur = (*schachbrett)[x][y] * player;
            if (aktuelle_figur > 0) {
                (*figuren_regeln[aktuelle_figur])(schachbrett, x, y, player, folgezustaende);
            }
        }
    }
    return folgezustaende;
}

bool schach_matt(BRETT* schachbrett, int player) {
    for (int x = 0; x < GROESSE; x++) {
        for (int y = 0; y < GROESSE; y++) {
            if ((*schachbrett)[x][y] == player * KOENIG)
                return false; // wir haben den König noch!
        }
    }
    return true; // keinen eigenen König gefunden → Schach matt!
}

int schach_zustandsbewertung(BRETT* schachbrett, int player) {
    int bewertung;
    if (DEBUG) {
        printf("zbf:\n");
        print_brett(schachbrett);
    }
    if (schach_matt(schachbrett, player))
        bewertung = -player * (INT_MAX - 3); // INT_MIN wäre gefährlich, INT_MAX benutzt minimax intern
    else if (schach_matt(schachbrett, -player))
        bewertung = player * (INT_MAX - 3);
    else {
        // TODO/FIXME: im Moment ist alles was nicht matt ist gleich gut...
        bewertung = 0;
    }
    if (DEBUG)
        printf("bewertung ist %d.\n", bewertung);
    return bewertung;
}

void strahlzuege(BRETT (*schachbrett), int x, int y, int dx, int dy, int player, int figur, LIST *folgezustaende) {
    assert(player == WHITE || player == BLACK);
    assert((*schachbrett)[x][y] == player * figur);
    int i = 1;
    bool geschlagen = false;
    while (!geschlagen &&
           !checkoutofbounds(x + dx*i, y + dy*i) &&
           ((*schachbrett)[x + dx*i][y + dy*i] * player) <= 0)
    {
        BRETT *copy = brett_cpy(schachbrett);
        if ((*schachbrett)[x + dx*i][y + dy*i] * -player > 0)
            geschlagen = true;
        (*copy)[x][y] = 0;
        (*copy)[x + dx*i][y + dy*i] = figur * player;
        list_append(folgezustaende, copy);
        i++;
    }
}

void laeuferzuege(BRETT* schachbrett, int x, int y, int player, LIST* folgezustaende) {
    assert((*schachbrett)[x][y] == LAEUFER * player && "Kein Laeufer auf der angegebenen Position.");
    strahlzuege(schachbrett, x, y, 1, 1, player, LAEUFER, folgezustaende);  // (x+i, y+i)
    strahlzuege(schachbrett, x, y, 1, -1, player, LAEUFER, folgezustaende); // (x+i, y-i)
    strahlzuege(schachbrett, x, y, -1, 1, player, LAEUFER, folgezustaende); // (x-i, y+i)
    strahlzuege(schachbrett, x, y, -1, -1, player, LAEUFER, folgezustaende); // (x-i, y-i)
}

void turmzuege(BRETT* schachbrett, int x, int y, int player, LIST* folgezustaende) {
    assert((*schachbrett)[x][y] == TURM * player && "Kein Turm auf der angegebenen Position.");
    strahlzuege(schachbrett, x, y, 1, 0, player, TURM, folgezustaende);
    strahlzuege(schachbrett, x, y, -1, 0, player, TURM, folgezustaende);
    strahlzuege(schachbrett, x, y, 0, 1, player, TURM, folgezustaende);
    strahlzuege(schachbrett, x, y, 0, -1, player, TURM, folgezustaende);
}

void damenzuege(BRETT* schachbrett, int x, int y, int player, LIST* folgezustaende) {
    assert((*schachbrett)[x][y] == DAME * player && "Keine Dame auf der angegebenen Position.");
    strahlzuege(schachbrett, x, y, 1, 1, player, DAME, folgezustaende);  // (x+i, y+i)
    strahlzuege(schachbrett, x, y, 1, -1, player, DAME, folgezustaende); // (x+i, y-i)
    strahlzuege(schachbrett, x, y, -1, 1, player, DAME, folgezustaende); // (x-i, y+i)
    strahlzuege(schachbrett, x, y, -1, -1, player, DAME, folgezustaende);

    strahlzuege(schachbrett, x, y, 1, 0, player, DAME, folgezustaende);
    strahlzuege(schachbrett, x, y, -1, 0, player, DAME, folgezustaende);
    strahlzuege(schachbrett, x, y, 0, 1, player, DAME, folgezustaende);
    strahlzuege(schachbrett, x, y, 0, -1, player, DAME, folgezustaende);

}

void feste_zuege(BRETT (*schachbrett), int x, int y, int dx, int dy, int player, int figur, LIST *folgezustaende) {
    if (!checkoutofbounds(x + dx, y + dy) &&
        ((*schachbrett)[x + dx][y - dy] * player) <= 0)
    {
        BRETT *copy = brett_cpy(schachbrett);
        (*copy)[x][y] = 0;
        (*copy)[x + dx][y + dy] = figur * player;
        list_append(folgezustaende, copy);
    }
}

void koenigszuege(BRETT* schachbrett, int x, int y, int player, LIST* folgezustaende) {
    //Läufer
    feste_zuege(schachbrett, x, y, 1, 1, player, KOENIG, folgezustaende);
    feste_zuege(schachbrett, x, y, 1, -1, player, KOENIG, folgezustaende);
    feste_zuege(schachbrett, x, y, -1, 1, player, KOENIG, folgezustaende);
    feste_zuege(schachbrett, x, y, -1, -1, player, KOENIG, folgezustaende);
    //Turm
    feste_zuege(schachbrett, x, y, 1, 0, player, KOENIG, folgezustaende);
    feste_zuege(schachbrett, x, y, -1, 0, player, KOENIG, folgezustaende);
    feste_zuege(schachbrett, x, y, 0, 1, player, KOENIG, folgezustaende);
    feste_zuege(schachbrett, x, y, 0, -1, player, KOENIG, folgezustaende);
}

void springerzuege(BRETT* schachbrett, int x, int y, int player, LIST* folgezustaende) {
    feste_zuege(schachbrett, x, y, 1, 2, player, SPRINGER, folgezustaende);
    feste_zuege(schachbrett, x, y, -1, 2, player, SPRINGER, folgezustaende);
    feste_zuege(schachbrett, x, y, 1, -2, player, SPRINGER, folgezustaende);
    feste_zuege(schachbrett, x, y, -1, -2, player, SPRINGER, folgezustaende);

    feste_zuege(schachbrett, x, y, 2, 1, player, SPRINGER, folgezustaende);
    feste_zuege(schachbrett, x, y, -2, 1, player, SPRINGER, folgezustaende);
    feste_zuege(schachbrett, x, y, 2, -1, player, SPRINGER, folgezustaende);
    feste_zuege(schachbrett, x, y, -2, -1, player, SPRINGER, folgezustaende);


}

void bauernzuege(BRETT* schachbrett, int x, int y, int player, LIST* folgezustaende) {
    if((player == 1 && y == 6) || (player == -1 && y == 2)) {
        feste_zuege(schachbrett, x, y, 0, 2, player, BAUER, folgezustaende);
        feste_zuege(schachbrett, x, y, 0, 1, player, BAUER, folgezustaende);
    }
    if((schachbrett[x-1][y-1] < 0 && player == 1) || (schachbrett[x+1][y-1] < 0 && player == 1)) {
        feste_zuege(schachbrett, x, y, -1, -1, player, BAUER, folgezustaende);
        feste_zuege(schachbrett, x, y, 1, -1, player, BAUER, folgezustaende);
    }
    else if((schachbrett[x-1][y+1] > 0 && player == -1)  || (schachbrett[x+1][y+1] > 0 && player == -1)) {
        feste_zuege(schachbrett, x, y, -1, 1, player, BAUER, folgezustaende);
        feste_zuege(schachbrett, x, y, 1, 1, player, BAUER, folgezustaende);
    }

    feste_zuege(schachbrett, x, y, 0, 1, player, BAUER, folgezustaende);
}

void print_brett(void* schachbrett_pointer) {
    BRETT* schachbrett = (BRETT*) schachbrett_pointer;
    printf("\n  ");
    for (int x=0; x < GROESSE; x++){
        printf(" %c", 'A' + x);
    }
    printf("\n");
    for (int x=0; x < GROESSE + 1; x++){
        printf("__");
    }
    printf("\n");
    for (int y=0; y < GROESSE; y++) {// i= spalten=y
        printf("%d|", y);
        for (int x = 0; x < GROESSE; x++) { //k=zeilen=x
            printf("%2d", (*schachbrett)[y][x]);
        }
        printf("\n");
    }
}
