#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "list.h"
#include "minimax.h"
#include "minimax.c"
#include "schach.h"
#include "schach.c"

BRETT initiale_position = {
        {4, 2, 3, 5, 6, 3, 2, 4},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-4, -2, -3, -5, -6, -3, -2, -4}
};


int positionsbewertung(LIST* aktuell_nachfolgerzustand, int player){

}


LIST* minimax(BRETT* schachbrett, int tiefe, int player) {
    LIST* nachfolgezustaende = schach_nachfolgezustaende(schachbrett, player);
    int spielergebnis = -INT_MAX * player; // besonders schlecht initialisieren
    LIST* bester_nachfolgezustand = NULL; // da speichern wir den besten drin
    LIST* aktueller_nachfolgezustand = NULL;


    for (int i = 0; i < list_size(nachfolgezustaende); i++) {

        aktueller_nachfolgezustand = list_get(nachfolgezustaende, i);
        int bewertung = 0;
        if(tiefe > 0) {
            bester_nachfolgezustand = minimax(aktueller_nachfolgezustand, tiefe - 1, -player);
        }
        else {
            bewertung = positionsbewertung(aktueller_nachfolgezustand, player);
        }
        if (bewertung * player > spielergebnis) {
            spielergebnis = bewertung;
            bester_nachfolgezustand = aktueller_nachfolgezustand;
        }
    }
    return bester_nachfolgezustand;
}

