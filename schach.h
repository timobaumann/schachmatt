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

/** Funktionen mit denen das Spielbrett gehandhabt wird (unabhängig von Schach-Regeln) */

void initialisieren(BRETT);
BRETT* brett_cpy(BRETT* in);
int brett_cmp(void* a, void* b);
bool brett_eql(void* a, void* b);

void print_brett(void* schachbrett_pointer);


int schach_next_player(int player);

/** Nachfolgezustände für die einzelnen Spielfiguren */

typedef void zuege_der_figur(BRETT* schachbrett, int x, int y, int player, LIST* folgezustaende);

/** findet alle Nachfolgezustaende des Spielbretts vom Laeufer auf x/y des Spielers player ausgehend */
zuege_der_figur laeuferzuege;
zuege_der_figur turmzuege;
zuege_der_figur damenzuege;
// TODO: hier Funktionen für weitere mögliche Figurenzüge hinzufügen


bool schach_matt(BRETT* schachbrett, int player);

/** was MiniMax braucht: Nachfolgezustände und Bewertungsfunktion für Zustände */
LIST* schach_nachfolgezustaende(BRETT* schachbrett, int player);

int schach_zustandsbewertung(BRETT* schachbrett, int player);

/** ein paar Spielzustände zur Initialisierung und zum Testen */

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

static BRETT end_game_1 = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, KOENIG, 0, 0, 0},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-4, -2, -3, -5, -6, -3, -2, -4},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
};

#endif //_SCHACH_H
