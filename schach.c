//
// Created by Anja Klosterhuber on 22.01.24.
//
#include <stdlib.h>
#include "schach.h"
#include <stdbool.h>
#include "list.h"
#include <string.h>

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

bool checkoutofbounds(int x, int y) {
    return x >= GROESSE || y >= GROESSE || x < 0 || y < 0;
}

BRETT* brett_cpy(BRETT in) {
    BRETT* out = calloc(1, sizeof(BRETT));
    memcpy(out, in, sizeof(BRETT));
    return out;
}

void initialisieren(BRETT schachbrett) {
    for (int y=0; y < GROESSE; y++) {// i= spalten=y
        for (int x = 0; x < GROESSE; x++) { //k=zeilen=x
            schachbrett[y][x] = initiale_position[y][x];
        }
    }
}

typedef void zuege_der_figur(BRETT schachbrett, int x, int y, int player, LIST* folgezustaende);
zuege_der_figur* figuren_regeln[6] = {
        &Bauer, &Laeuferzuege, &Springer, &Turm, &Dame, &Konig
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

void Laeuferzuege(BRETT schachbrett, int x, int y, int player, LIST* folgezustaende) {
    int MAX_STEPS = GROESSE -1 ;
    int directions[4][2] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
    // NW
    int i = 1;
    bool geschlagen = false;
    while (i < MAX_STEPS && !geschlagen && !checkoutofbounds(x-i, y-i) && (schachbrett[y-i][x-i] * player) <= 0) {
        BRETT* copy = brett_cpy(schachbrett);
        if (schachbrett[y-i][x-i] * -player > 0)
            geschlagen = true;
        (*copy)[y][x] = 0;
        (*copy)[y-i][x-i] = LAEUFER * player;
        list_append(folgezustaende, copy);
    }
    // NO
    // SO
    // SW
}

void Dame(BRETT schachbrett, int x, int y, int player, LIST* folgezustaende) {
    Turm(schachbrett, x, y, player, folgezustaende);
    Laeuferzuege(schachbrett, x, y, player, folgezustaende);
}

int BauerS(int (*schachbrett)[GROESSE], int n1, int n2,int x1, int x2, int y1, int y2) {
    int zug=0;
    if (n1 == 0 && n2 == -1) { //Bauer normaler Zug
        if(schachbrett[x2][y2] == 0) {
        }else{
            zug = -1;
        }
    }
    else if(n1 == 0 && n2 == -2 && x1 == 6) { //Bauer 1. Zug
    }
    else if((((schachbrett[x2][y2] != 0) && ((n1 == -1 && n2 == -1)) || (n1 == 1 && n2 == -1)))&& x1 == 6) { //Bauer 1. Zug schlag
    }
    else {
        zug = -1;
    }
    return zug;
}

int BauerW (int (*schachbrett)[GROESSE], int n1, int n2,int x1, int x2, int y1, int y2) {
    int zug=0;
    if (n1 == 0 && n2 == 1) { //Bauer normaler Zug
        if(schachbrett[x2][y2] == 0) {
        }else{
            zug=-1;
        }
    }
    else if(n1 == 0 && n2 == 2 && x1 == 2) { //Bauer 1. Zug
    }
    else if((((schachbrett[x2][y2] != 0) && ((n1 == 1 && n2 == 1)) || (n1 == -1 && n2 == 1)))&& x1 == 2) { //Bauer 1. Zug schlag
    }
    else {
        zug=-1;
    }
    return zug;
}

int Springer (int (*schachbrett)[GROESSE], int n1, int n2, int x1, int x2, int y1, int y2) {
    int zug=0;

    if((n1==1 && n2==2) || (n1==-1 && n2==2 ) || (n1==1 && n2==-2) || (n1==-1 && n2==-2) || (n1==2 && n2==1) || (n1==-2 && n2==1) || (n1==2 && n2==-1) || (n1==-2 && n2==-1)){
        if(schachbrett[x2][y2] >= 0){

        } else {
            zug=-1;
        }
    } else {
        zug=-1;
    }

    return zug;
}

int Laufer (int (*schachbrett)[GROESSE], int n1, int n2, int x1, int x2, int y1, int y2) {
    int zug = 0;
    if(n1 == n2) { //Läufer Zug
        if(n1>0) {
            for (int i = 1; i < n1; i++) {
                if (schachbrett[x1 + i][y1 + i] != 0) { //Überprüfung auf Spielfiguren
                    zug = -1;
                }
            }
        }
        if(n1<0) {
            for (int i = -1; i > n1; i--) {
                if (schachbrett[x1 + i][y1 + i] != 0) { //Überprüfung auf Spielfiguren
                    zug = -1;
                }
            }
        }
    } else if(abs(n1) == abs(n2)) {
        if(n1>0 && n2<0) {
            for (int i = 1; i < n1; i++) {
                if (schachbrett[x1 - i][y1 + i] != 0) { //Überprüfung auf Spielfiguren
                    zug = -1;
                }
            }
        }
        else if(n1<0 && n2>0) {
            for (int i = 1; i < n2; i++) {
                if (schachbrett[x1 + i][y1 - i] != 0) { //Überprüfung auf Spielfiguren
                    zug = -1;
                }
            }
        }
    }
    else {
        zug = -1;
    }


    return zug;

}

int Turm (int (*schachbrett)[GROESSE], int n1, int n2, int x1, int x2, int y1, int y2) {
    int zug = 0;
    if (n1 != 0 && n2 == 0) {
        if (n1>0) { //Turm rechts
            for (int i = 1; i < n1; i++) {
                if (schachbrett[x1][y1 + i] != 0) {
                    zug= -1;
                    return zug;
                }
            }

        } else if (n1<0) {//Turm links
            for (int i = -1; i > n1; i--) {
                if (schachbrett[x1][y1 + i] != 0) {
                    zug = -1;
                    return zug;
                }
            }
        }

    } else if (n1 == 0 && n2 != 0) {
        if(n2>0) { //Turm vor
            for (int i = 1; i < n2; i++) {
                if (schachbrett[x1 + i][y1] != 0) {
                    zug= -1;
                    return zug;
                }
            }
        } else if (n2<0) { //Turm rück
            for (int i = -1; i > n2; i--) {
                if (schachbrett[x1 + i][y1] != 0) {
                    zug = -1;
                    return zug;
                }
            }
        }
    } else {
        zug = -1;
    }
    return zug;
}

