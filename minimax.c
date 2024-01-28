//
// Created by timo on 28.01.24.
//

#include "minimax.h"
#include <assert.h>
#include <stdio.h> // NULL
#include <limits.h> // INT_MAX
#include <stdlib.h>

typedef PAYLOAD ZUSTAND;


/** auf den unteren Ebenen liefert Minimax uns jeweils die Bewertung für den Zustand zurück,
 * auf der obersten Ebene hingegen einen zufällig ausgewählten unter denen die am besten bewertet sind.
 */
int _minimax_untere_ebenen(ZUSTAND z, int tiefe, int player, nachfolgezustandsfunktion nzf, zustandsbewertungsfunktion zbf) {
    assert((player == 1 || player == -1) && "Player must be +/- 1");
    int beste_bewertung = -INT_MAX * player; // besonders schlecht initialisieren

    LIST* nachfolgezustaende = nzf(z, player);
    for (int i = 0; i < list_size(nachfolgezustaende); i++) {
        ZUSTAND aktueller_nachfolgezustand = list_get(nachfolgezustaende, i);
        int bewertung = 0;
        if (tiefe > 0) {
            bewertung = _minimax_untere_ebenen(aktueller_nachfolgezustand, tiefe - 1, -player, nzf, zbf);
        } else {
            bewertung = zbf(aktueller_nachfolgezustand, player);
        }
        if (bewertung * player > beste_bewertung) {
            beste_bewertung = bewertung;
        }
    }
    return beste_bewertung;
}

/* return a truly uniform random value in the range 0..n-1 inclusive */
int rand_in_range(int n) {
    int limit;
    int r;
    limit = RAND_MAX - (RAND_MAX % n);
    while((r = rand()) >= limit);
    return r % n;
}

ZUSTAND _minimax_oberste_ebene(ZUSTAND z, int tiefe, int player, nachfolgezustandsfunktion nzf, zustandsbewertungsfunktion zbf) {
    int beste_bewertung = -INT_MAX * player; // besonders schlecht initialisieren
    LIST* beste_nachfolgezustaende = list_new(); // da speichern wir (alle) besten drin

    LIST* nachfolgezustaende = nzf(z, player);
    for (int i = 0; i < list_size(nachfolgezustaende); i++) {
        ZUSTAND aktueller_nachfolgezustand = list_get(nachfolgezustaende, i);
        int bewertung = 0;
        if (tiefe > 0) {
            bewertung = _minimax_untere_ebenen(aktueller_nachfolgezustand, tiefe - 1, -player, nzf, zbf);
        } else {
            bewertung = zbf(aktueller_nachfolgezustand, -player);
        }
        if (bewertung * player > beste_bewertung) {
            beste_nachfolgezustaende = list_new();
            beste_bewertung = bewertung;
            list_append(beste_nachfolgezustaende, aktueller_nachfolgezustand);
        }
    }
    int zufaelliger_zustand = rand_in_range(list_size(beste_nachfolgezustaende));
    ZUSTAND ein_bester_nachfolgezustand = list_get(beste_nachfolgezustaende, zufaelliger_zustand);
    beste_nachfolgezustaende = list_remove(beste_nachfolgezustaende, zufaelliger_zustand);
    list_free(beste_nachfolgezustaende);
    return ein_bester_nachfolgezustand;
}

ZUSTAND minimax(ZUSTAND z, int tiefe, int player, nachfolgezustandsfunktion nzf, zustandsbewertungsfunktion zbf) {
    _minimax_oberste_ebene(z, tiefe, player, nzf, zbf);
}
