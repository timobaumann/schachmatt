//
// Created by Anja Klosterhuber on 22.01.24.
//
#ifndef _SCHACH_H
#define _SCHACH_H

#include "list.h"

/** Zuordnung von Zahlwerten zu den beiden Spielern: */
#define WHITE 1
#define BLACK -1

/** Konstanten für die Sorten der Spielfiguren: */
#define BAUER 1
#define TURM 4
#define LAEUFER 2
#define SPRINGER 3
#define KOENIG 6
#define DAME 5

/** Das Spielbrett ist immer 8 Felder groß. */
#define GROESSE 8

typedef int BRETT[GROESSE][GROESSE];

void initialisieren(BRETT);
BRETT* brett_cpy(BRETT* in);
int brett_cmp(void* a, void* b);
bool brett_eql(void* a, void* b);

void print_brett(void* schachbrett_pointer);

/*int BauerW (BRETT, int n1, int n2, int x1, int x2, int y1, int y2);
int BauerS (BRETT, int n1, int n2, int x1, int x2, int y1, int y2);
int Laufer (BRETT, int n1, int n2, int x1, int x2, int y1, int y2);
int Turm (BRETT, int n1, int n2, int x1, int x2, int y1, int y2);
int Springer (BRETT, int n1, int n2, int x1, int x2, int y1, int y2);
 */
/** findet alle Nachfolgezustaende des Spielbretts vom Laeufer auf x/y des Spielers player ausgehend */
void laeuferzuege(BRETT* schachbrett, int x, int y, int player, LIST* folgezustaende);
// TODO: hier weitere mögliche Figurenzüge hinzufügen

LIST* schach_nachfolgezustaende(BRETT* schachbrett, int player);

static BRETT triviales_brett = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, LAEUFER, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
};

static BRETT initiales_brett = {
        {4, 2, 3, 5, 6, 3, 2, 4},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-4, -2, -3, -5, -6, -3, -2, -4}
};



#endif //_SCHACH_H
