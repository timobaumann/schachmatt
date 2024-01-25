//
// Created by Anja Klosterhuber on 22.01.24.
//
#include <stdbool.h>

#ifndef AGKIPROJEKTSCHACH_SCHACH_H
#define AGKIPROJEKTSCHACH_SCHACH_H

#define GROESSE 8

typedef int BRETT[GROESSE][GROESSE];

#define WHITE 1
#define BLACK -1
#define BAUER 1
#define TURM 4
#define LAEUFER 2
#define SPRINGER 3
#define KOENIG 6
#define DAME 5

void initialisieren(BRETT);
int BauerW (BRETT, int n1, int n2, int x1, int x2, int y1, int y2);
int BauerS (BRETT, int n1, int n2, int x1, int x2, int y1, int y2);
int Laufer (BRETT, int n1, int n2, int x1, int x2, int y1, int y2);
int Turm (BRETT, int n1, int n2, int x1, int x2, int y1, int y2);
int Springer (BRETT, int n1, int n2, int x1, int x2, int y1, int y2);
void Laeuferzuege(BRETT schachbrett, int x, int y, int player, LIST* folgezustaende);
BRETT triviales_brett = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, LAEUFER, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
};



#endif //AGKIPROJEKTSCHACH_SCHACH_H
