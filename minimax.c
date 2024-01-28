//
// Created by timo on 28.01.24.
//

#include "minimax.h"
#include "list.h"
#include <stdio.h> // NULL
#include <limits.h> // INT_MAX

ZUSTAND* _minimax(ZUSTAND* schachbrett, int tiefe, int player, nachfolgezustandsfunktion nzf, zustandsbewertungsfunktion zbf) {
    int beste_bewertung = -INT_MAX * player; // besonders schlecht initialisieren
    ZUSTAND* bester_nachfolgezustand = NULL; // da speichern wir den besten drin

    LIST* nachfolgezustaende = nzf(schachbrett, player);
    for (int i = 0; i < list_size(nachfolgezustaende); i++) {
        ZUSTAND* aktueller_nachfolgezustand = list_get(nachfolgezustaende, i);
        int bewertung = 0;
        if (tiefe > 0) {
            bester_nachfolgezustand = minimax(aktueller_nachfolgezustand, tiefe - 1, -player);
        } else {
            bewertung = zbf(aktueller_nachfolgezustand, player);
        }
        if (bewertung * player > beste_bewertung) {
            beste_bewertung = bewertung;
            bester_nachfolgezustand = aktueller_nachfolgezustand;
        }
    }
    return bester_nachfolgezustand;
}

ZUSTAND* minimax(ZUSTAND* schachbrett, int tiefe, int player, nachfolgezustandsfunktion nzf, zustandsbewertungsfunktion zbf) {
    _minimax(schachbrett, tiefe, player, nzf, zbf);
}