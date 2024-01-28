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
/*
void Bauerzug(BRETT , int , int , int , LIST* );
void Springerzug(BRETT , int , int , int , LIST* );
void Laeuferzug(BRETT , int , int , int , LIST* );
void Turmzug(BRETT , int , int , int , LIST* );
void Damezug(BRETT , int , int , int , LIST* );
void Konigzug(BRETT , int , int , int , LIST* );
*/
bool checkoutofbounds(int x, int y) {
    return x >= GROESSE || y >= GROESSE || x < 0 || y < 0;
}

BRETT* brett_cpy(BRETT in) {
    BRETT* out = calloc(1, sizeof(BRETT));
    memcpy(out, in, sizeof(BRETT));
    return out;
}

void initialisieren(BRETT schachbrett) {
    memcpy(schachbrett, initiales_brett, sizeof(BRETT));
}

typedef void zuege_der_figur(BRETT schachbrett, int x, int y, int player, LIST* folgezustaende);
zuege_der_figur* figuren_regeln[6] = {
        /*Bauerzug,*/
        &Laeuferzug, /*&Springerzug, &Turmzug, &Damezug, &Konigzug*/
};

LIST* schach_nachfolgezustaende(int (*schachbrett)[GROESSE], int player) {
    LIST* folgezustaende = list_new();
    for (int y= 0; y < GROESSE; y++) {
        for (int x = 0; x < GROESSE; x++) {
            int aktuelle_figur = schachbrett[y][x] * player;
            if (aktuelle_figur > 0) {
                (*figuren_regeln[aktuelle_figur])(schachbrett, x, y, player, folgezustaende);
            }
        }
    }
    return folgezustaende;
}

/*
int positionsbewertung(LIST* aktuell_nachfolgezustand, int player){


}


LIST* minimax(BRETT schachbrett, int tiefe, int player) {
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

*/

void Zuege(BRETT schachbrett, int x, int y, int dx, int dy, int player, LIST* folgezustaende) {
    int MAX_STEPS = GROESSE - 1;
    int directions[4][2] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
    int i = 1;
    bool geschlagen = false;
    while (i < MAX_STEPS && !geschlagen && !checkoutofbounds(x+ dx*i, y + dy*i) && (schachbrett[y-i][x-i] * player) <= 0) {
        BRETT *copy = brett_cpy(schachbrett);
        if (schachbrett[y + dx*i][x + dy*i] * -player > 0)
            geschlagen = true;
        (*copy)[y][x] = 0;
        (*copy)[y + dx*i][x + dy*i] = LAEUFER * player;
        list_append(folgezustaende, copy);
        i++;
    }

}

void Laeuferzug(BRETT schachbrett, int x, int y, int player, LIST* folgezustaende) {
    assert(player == WHITE || player == BLACK);
    Zuege(schachbrett, x, y, 1, 1, player, folgezustaende);  // (x+i, y+i)
    Zuege(schachbrett, x, y, 1, -1, player, folgezustaende); // (x+i, y-i)
    Zuege(schachbrett, x, y, -1, 1, player, folgezustaende); // (x-i, y+i)
    Zuege(schachbrett, x, y, -1, -1, player, folgezustaende); // (x-i, y-i)
}

void Turmzug(BRETT schachbrett, int x, int y, int player, LIST* folgezustaende) {
    Zuege(schachbrett, x, y, 1, 0, player, folgezustaende);
    Zuege(schachbrett, x, y, -1, 0, player, folgezustaende);
    Zuege(schachbrett, x, y, 0, 1, player, folgezustaende);
    Zuege(schachbrett, x, y, 0, -1, player, folgezustaende);
}

void Damezug(BRETT schachbrett, int x, int y, int player, LIST* folgezustaende) {
    Laeuferzug(schachbrett,  x,  y, player, folgezustaende);
    Turmzug( schachbrett,  x,  y, player, folgezustaende);
}

void Konigzuege(BRETT schachbrett, int x, int y, int dx, int dy, int player, LIST* folgezustaende) {
    int MAX_STEPS = GROESSE -1 ;
    int directions[4][2] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
    int i = 1;
    bool geschlagen = false;
    if (!geschlagen && !checkoutofbounds(x+ dx*i, y + dy*i) && (schachbrett[y-i][x-i] * player) <= 0) {
        BRETT *copy = brett_cpy(schachbrett);
        if (schachbrett[y + dx*i][x + dy*i] * -player > 0)
            geschlagen = true;
        (*copy)[y][x] = 0;
        (*copy)[y + dx*i][x + dy*i] = LAEUFER * player;
        list_append(folgezustaende, copy);
    }
}

void Konigzug(BRETT schachbrett, int x, int y, int player, LIST* folgezustaende) {
    //Laufer
    Konigzuege(schachbrett, x, y, 1, 1, player, folgezustaende);
    Konigzuege(schachbrett, x, y, 1, -1, player, folgezustaende);
    Konigzuege(schachbrett, x, y, -1, 1, player, folgezustaende);
    Konigzuege(schachbrett, x, y, -1, -1, player, folgezustaende);
    //Turm
    Konigzuege(schachbrett, x, y, 1, 0, player, folgezustaende);
    Konigzuege(schachbrett, x, y, -1, 0, player, folgezustaende);
    Konigzuege(schachbrett, x, y, 0, 1, player, folgezustaende);
    Konigzuege(schachbrett, x, y, 0, -1, player, folgezustaende);
}

void Springerzug(BRETT schachbrett, int x, int y, int player, LIST* folgezustaende) {
    Konigzuege(schachbrett, x, y, 1, 2, player, folgezustaende);
    Konigzuege(schachbrett, x, y, -1, 2, player, folgezustaende);
    Konigzuege(schachbrett, x, y, 1, -2, player, folgezustaende);
    Konigzuege(schachbrett, x, y, -1, -2, player, folgezustaende);

    Konigzuege(schachbrett, x, y, 2, 1, player, folgezustaende);
    Konigzuege(schachbrett, x, y, -2, 1, player, folgezustaende);
    Konigzuege(schachbrett, x, y, 2, -1, player, folgezustaende);
    Konigzuege(schachbrett, x, y, -2, -1, player, folgezustaende);


}

void Bauerzug(BRETT schachbrett, int x, int y, int player, LIST* folgezustaende) {
    if((player == 1 && y == 6) || (player == -1 && y == 2)) {
        Konigzuege(schachbrett, x, y, 0, 2, player, folgezustaende);
        Konigzuege(schachbrett, x, y, 0, 1, player, folgezustaende);
    }
    if((schachbrett[x-1][y-1] < 0 && player == 1) || (schachbrett[x+1][y-1] < 0 && player == 1)) {
        Konigzuege(schachbrett, x, y, -1, -1, player, folgezustaende);
        Konigzuege(schachbrett, x, y, 1, -1, player, folgezustaende);
    }
    else if((schachbrett[x-1][y+1] > 0 && player == -1)  || (schachbrett[x+1][y+1] > 0 && player == -1)) {
        Konigzuege(schachbrett, x, y, -1, 1, player, folgezustaende);
        Konigzuege(schachbrett, x, y, 1, 1, player, folgezustaende);
    }

    Konigzuege(schachbrett, x, y, 0, 1, player, folgezustaende);
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
            if((*schachbrett)[y][x]>=0) {
                printf(" ");
            }
            printf("%d", (*schachbrett)[y][x]);
        }
        printf("\n");
    }
}

