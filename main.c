#include <stdio.h>
#include <stdlib.h>
#include "schach.h"
#include <limits.h>
// agki projekt schach

void spielzug(int(*)[], int);


bool checkoutofbounds(int x, int y) {
    return x >= GROESSE || y >= GROESSE || x < 0 || y < 0;
}

int pruffigur(int x, int y, int (*schachbrett)[8]) {
    int spielfigur = schachbrett[x][y];
    if(spielfigur >= 0) {
        printf("Die Position ist nicht besetzt, du hast darauf KEINEN ZUGRIFF!\n");
        return 1;
    }
    return 0;
}

void ausgeben(int (*schachbrett)[8]) {
    int zahl = GROESSE - 1;
    for (int x=0; x < GROESSE; x++){
        printf(" %c " , 'A' + x);
/*
        switch(x){
            case 0: printf(" A ");break;
            case 1: printf("B ");break;
            case 2: printf("C ");break;
            case 3: printf("D ");break;
            case 4: printf("E ");break;
            case 5: printf("F ");break;
            case 6: printf("G ");break;
            case 7: printf("H");break;

            default:printf("Das sollte nie zu sehen sein!");break;
        }
*/
    }
    printf("\n");

    for (int x=0; x < GROESSE + 1; x++){
        printf("__");
    }
    printf("\n");

    for (int y=0; y < GROESSE; y++) {// i= spalten=y
        printf("%d|", y);
        for (int x = 0; x < GROESSE; x++) { //k=zeilen=x
            if(schachbrett[y][x]>=0) {
                printf(" ");
            }
            printf("%d", schachbrett[y][x]);
        }
        printf("\n");
    }
}

void spielfigur (int (*schachbrett)[8], int grosse, int n1, int n2, int x1, int y1, int x2, int y2) {
    int zug = 0;
    switch (schachbrett[x1][y1]) {
        case -1: { //Bauer
            if (BauerS(schachbrett, n1, n2, x1, x2, y1, y2) == 0) {
                schachbrett[x1][y1] = 0;
                schachbrett[x2][y2] = -1;
            } else {
                printf("Die Spielfigur Bauer kann so nicht gehen!\n");
                spielzug(schachbrett, grosse);
            }
        }
            break;

        case -2: { //Springer
            if (Springer(schachbrett, n1, n2, x1, x2, y1, y2) == 0) {
                schachbrett[x1][y1] = 0;
                schachbrett[x2][y2] = -2;
            } else {
                printf("Die Spielfigur Springer kann so nicht gehen!\n");
                spielzug(schachbrett, grosse);
            }
        }
            break;

        case -3: { //Läufer
            if (Laufer(schachbrett, n1, n2, x1, x2, y1, y2) == 0) {
                schachbrett[x1][y1] = 0;
                schachbrett[x2][y2] = -3;
            } else {
                printf("Die Spielfigur Laufer kann so nicht gehen!\n");
                spielzug(schachbrett, grosse);
            }
        }
            break;

        case -4: { //Turm
            if (Turm(schachbrett, n1, n2, x1, x2, y1, y2) == 0) {
                schachbrett[x1][y1] = 0;
                schachbrett[x2][y2] = -4;
            } else {
                printf("Die Spielfigur Turm kann so nicht gehen!\n");
                spielzug(schachbrett, grosse);
            }
        }
            break;

        case -5: { //Dame
            if (abs(n1) == abs(n2)) {
                if (Laufer(schachbrett, n1, n2, x1, x2, y1, y2) == 0) {
                    schachbrett[x1][y1] = 0;
                    schachbrett[x2][y2] = -5;
                } else {
                    printf("Die Spielfigur Dame kann so nicht gehen!\n");
                    spielzug(schachbrett, grosse);
                }
            } else if ((n1 != 0 && n2 == 0) || n1 == 0 && n2 != 0) {
                if (Turm(schachbrett, n1, n2, x1, x2, y1, y2) == 0) {
                    schachbrett[x1][y1] = 0;
                    schachbrett[x2][y2] = -5;
                } else {
                    printf("Die Spielfigur Dame kann so nicht gehen!\n");
                    spielzug(schachbrett, grosse);
                }
            } else {
                printf("Die Dame darf nicht so laufen!\n");
                spielzug(schachbrett, grosse);
            }
        }
            break;

        case -6: { //König
            if (abs(n1) == 1 && abs(n2) == 1) {
                if (Laufer(schachbrett, n1, n2, x1, x2, y1, y2) == 0) {
                    schachbrett[x1][y1] = 0;
                    schachbrett[x2][y2] = -6;
                } else {
                    printf("Die Spielfigur Konig kann so nicht gehen!\n");
                    spielzug(schachbrett, grosse);
                }
            } else if ((abs(n1) == 1 && n2 == 0) || (n1 == 0 && abs(n2) == 0)) {
                if (Turm(schachbrett, n1, n2, x1, x2, y1, y2) == 0) {
                    schachbrett[x1][y1] = 0;
                    schachbrett[x2][y2] = -6;
                } else {
                    printf("Die Koenig darf nicht so laufen!\n");
                    spielzug(schachbrett, grosse);
                }
            }
            break;

            default: {
                printf("Die Schritte passen nicht, taetige einen neuen Spielzug!\n");
                spielzug(schachbrett, grosse);
            }
            break;
        }
    }
}

int schachWK (int (*schachbrett)[8], int grosse) {

    int x1 = 0; int y1 = 0;
    int x1T = 0; int y1T = 0; int x1D = 0; int y1D = 0; int x1K = 0; int y1K = 0;
    int posxW=0;
    int posyW=0;
    int fig = 0;

    int schach=0;

    //Prüf auf Bauer schwarz
    for(int i=0; i<8; i++) { //Suche Bauer
        for(int j=0; j<8; j++) {
            if(schachbrett[i][j] == -1) {
                x1=i;
                y1=j;
                if(prufoutofbounds(x1 + 1, y1 - 1, 8) == 0) {
                    if(schachbrett[x1 + 1][y1 - 1] == 6) {
                        printf("Schach! (Bauer)\n");

                    }
                }
                if(prufoutofbounds(x1 - 1, y1 - 1, 8) == 0) {
                    if(schachbrett[x1 - 1][y1 - 1] == 6) {
                        printf("Schach! (Bauer)\n");
                    }
                }
            }
        }
    }

    //Prüf Springer schwarz
    for(int i=0; i<8; i++) { //Suche Springer
        for(int j=0; j<8; j++) {
            if(schachbrett[i][j] == -2) {
                x1=i;
                y1=j;
                if(prufoutofbounds(x1 + 1, y1 + 2, 8) == 0) {
                    if (schachbrett[x1 + 1][y1 + 2] == 6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 + 1, y1 - 2, 8) == 0) {
                    if (schachbrett[x1 + 1][y1 - 2] == 6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 - 1, y1 + 2, 8) == 0) {
                    if (schachbrett[x1 - 1][y1 + 2] == 6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 - 1, y1 - 2, 8) == 0) {
                    if (schachbrett[x1 - 1][y1 - 2] == 6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 + 2, y1 + 1, 8) == 0) {
                    if (schachbrett[x1 + 2][y1 + 1] == 6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 + 2, y1 - 1, 8) == 0) {
                    if (schachbrett[x1 + 2][y1 - 1] == 6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 - 2, y1 + 1, 8) == 0) {
                    if (schachbrett[x1 - 2][y1 + 1] == 6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 - 2, y1 - 1, 8) == 0) {
                    if (schachbrett[x1 - 2][y1 - 1] == 6) {
                        printf("Schach! (Springer)\n");
                    }
                }
            }
        }
    }


    //Prüf Läufer & Dame schwarz
    for(int i=0; i<8; i++) { //Suche Läufer
        for(int j=0; j<8; j++) {
            if(schachbrett[i][j] == -3) {
                x1=i;
                y1=j;
                for(int n=0; n<8; n++) {
                    if (prufoutofbounds(x1 + n, y1 + n, 8) == 0) {
                        if (schachbrett[x1 + n][y1 + n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Laufer)\n");
                        }
                    }
                    if (prufoutofbounds(x1 + n, y1 - n, 8) == 0) {
                        if (schachbrett[x1 + n][y1 - n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Laufer)\n");
                        }
                    }
                    if (prufoutofbounds(x1 - n, y1 + n, 8) == 0) {
                        if (schachbrett[x1 - n][y1 + n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Laufer)\n");
                        }
                    }
                    if (prufoutofbounds(x1 - n, y1 - n, 8) == 0) {
                        if (schachbrett[x1 - n][y1 - n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Laufer)\n");
                        }
                    }
                }
            }
            if(schachbrett[i][j] == -5) { //Suche Dame
                x1D=i;
                y1D=j;
                //Prüf Dame schwarz
                for(int n=0; n<8; n++) {
                    if (prufoutofbounds(x1D + n, y1D + n, 8) == 0) {
                        if (schachbrett[x1D + n][y1D + n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D + n, y1D - n, 8) == 0) {
                        if (schachbrett[x1D + n][y1D - n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D - n, y1D + n, 8) == 0) {
                        if (schachbrett[x1D - n][y1D + n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D - n, y1D - n, 8) == 0) {
                        if (schachbrett[x1D - n][y1D - n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                }
            }
        }
    }

    //Prüf Turm & Dame schwarz
    fig = 0;
    for(int i=0; i<8; i++) { //Suche Turm
        for(int j=0; j<8; j++) {
            if(schachbrett[i][j] == -4) {
                x1T=i;
                y1T=j;
                for(int n=0; n<8; n++) {
                    if (prufoutofbounds(x1T + n, y1T, 8) == 0) {
                        if (schachbrett[x1T + n][y1T] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Turm)\n");
                        }
                    }
                    if (prufoutofbounds(x1T - n, y1T, 8) == 0) {
                        if (schachbrett[x1T - n][y1T] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Turm)\n");
                        }
                    }
                    if (prufoutofbounds(x1T, y1T + n, 8) == 0) {
                        if (schachbrett[x1T][y1T + n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Turm)\n");
                        }
                    }
                    if (prufoutofbounds(x1T, y1T - n, 8) == 0) {
                        if (schachbrett[x1T][y1T - n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Turm)\n");
                        }
                    }
                }
            }
            if(schachbrett[i][j] == -5) { //Suche Dame
                x1D=i;
                y1D=j;
                //Prüf Dame schwarz
                for(int n=0; n<8; n++) {
                    if (prufoutofbounds(x1D + n, y1D, 8) == 0) {
                        if (schachbrett[x1D + n][y1D] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D - n, y1D, 8) == 0) {
                        if (schachbrett[x1T - n][y1T] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D, y1D + n, 8) == 0) {
                        if (schachbrett[x1D][y1D + n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D, y1D - n, 8) == 0) {
                        if (schachbrett[x1D][y1D - n] == 6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                }
            }
        }
    }

    //Prüf König schwarz
    for(int i=0; i<8; i++) {
        for (int j = 0; j < 8; j++) {
            if (schachbrett[i][j] == -6) { //Suche König
                x1D = i;
                y1D = j;
                //Prüf König schwarz
                if (prufoutofbounds(x1 + 1, y1 + 1, 8) == 0) {
                    if (schachbrett[x1 + 1][y1 + 1] == 6) { //Überprüfung auf König Weiß
                        printf("Schach! (König)\n");
                    }
                }
                if (prufoutofbounds(x1 + 1, y1 - 1, 8) == 0) {
                    if (schachbrett[x1 + 1][y1 - 1] == 6) { //Überprüfung auf König Weiß
                        printf("Schach! (König)\n");
                    }
                }
                if (prufoutofbounds(x1 - 1, y1 + 1, 8) == 0) {
                    if (schachbrett[x1 - 1][y1 + 1] == 6) { //Überprüfung auf König Weiß
                        printf("Schach! (König)\n");
                    }
                }
                if (prufoutofbounds(x1 - 1, y1 - 1, 8) == 0) {
                    if (schachbrett[x1 - 1][y1 - 1] == 6) { //Überprüfung auf König Weiß
                        printf("Schach! (König)\n");
                    }
                }

                if (prufoutofbounds(x1 + 1, y1, 8) == 0) {
                    if (schachbrett[x1 + 1][y1] == 6) { //Überprüfung auf König Weiß
                        printf("Schach! (König)\n");
                    }
                }
                if (prufoutofbounds(x1 - 1, y1, 8) == 0) {
                    if (schachbrett[x1 - 1][y1] == 6) { //Überprüfung auf König Weiß
                        printf("Schach! (Dame)\n");
                    }
                }
                if (prufoutofbounds(x1, y1 + 1, 8) == 0) {
                    if (schachbrett[x1][y1 + 1] == 6) { //Überprüfung auf König Weiß
                        printf("Schach! (Dame)\n");
                    }
                }
                if (prufoutofbounds(x1, y1 - 1, 8) == 0) {
                    if (schachbrett[x1][y1 - 1] == 6) { //Überprüfung auf König Weiß

                        printf("Schach! (Dame)\n");
                    }
                }
            }
        }
    }
    /*//-1 schachmatt -> abrrechen -> main ausprinten winner
    //0 bei schach -> schach printen -> weiter
    //1 nicht egfärdet
     */
    return 0;
}

int schachSK (int (*schachbrett)[8], int grosse) {

    int x1 = 0; int y1 = 0;
    int x1T = 0; int y1T = 0; int x1D = 0; int y1D = 0; int x1K = 0; int y1K = 0;
    int posxW=0;
    int posyW=0;
    int fig = 0;

    int schach=0;
    //Prüf auf Bauer weiß
    for(int i=0; i<8; i++) { //Suche Bauer
        for(int j=0; j<8; j++) {
            if(schachbrett[i][j] == 1) {
                x1=i;
                y1=j;
                if(prufoutofbounds(x1 + 1, y1 - 1, 8) == 0) {
                    if(schachbrett[x1 + 1][y1 - 1] == -6) {
                        printf("Schach! (Bauer)\n");

                    }
                }
                if(prufoutofbounds(x1 - 1, y1 - 1, 8) == 0) {
                    if(schachbrett[x1 - 1][y1 - 1] == -6) {
                        printf("Schach! (Bauer)\n");
                    }
                }
            }
        }
    }

    //Prüf Springer weiß
    for(int i=0; i<8; i++) { //Suche Springer
        for(int j=0; j<8; j++) {
            if(schachbrett[i][j] == 2) {
                x1=i;
                y1=j;
                if(prufoutofbounds(x1 + 1, y1 + 2, 8) == 0) {
                    if (schachbrett[x1 + 1][y1 + 2] == -6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 + 1, y1 - 2, 8) == 0) {
                    if (schachbrett[x1 + 1][y1 - 2] == -6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 - 1, y1 + 2, 8) == 0) {
                    if (schachbrett[x1 - 1][y1 + 2] == -6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 - 1, y1 - 2, 8) == 0) {
                    if (schachbrett[x1 - 1][y1 - 2] == -6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 + 2, y1 + 1, 8) == 0) {
                    if (schachbrett[x1 + 2][y1 + 1] == -6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 + 2, y1 - 1, 8) == 0) {
                    if (schachbrett[x1 + 2][y1 - 1] == -6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 - 2, y1 + 1, 8) == 0) {
                    if (schachbrett[x1 - 2][y1 + 1] == -6) {
                        printf("Schach! (Springer)\n");
                    }
                }
                if(prufoutofbounds(x1 - 2, y1 - 1, 8) == 0) {
                    if (schachbrett[x1 - 2][y1 - 1] == -6) {
                        printf("Schach! (Springer)\n");
                    }
                }
            }
        }
    }


    //Prüf Läufer & Dame weiß
    for(int i=0; i<8; i++) { //Suche Läufer
        for(int j=0; j<8; j++) {
            if(schachbrett[i][j] == 3) {
                x1=i;
                y1=j;
                for(int n=0; n<8; n++) {
                    if (prufoutofbounds(x1 + n, y1 + n, 8) == 0) {
                        if (schachbrett[x1 + n][y1 + n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Laufer)\n");
                        }
                    }
                    if (prufoutofbounds(x1 + n, y1 - n, 8) == 0) {
                        if (schachbrett[x1 + n][y1 - n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Laufer)\n");
                        }
                    }
                    if (prufoutofbounds(x1 - n, y1 + n, 8) == 0) {
                        if (schachbrett[x1 - n][y1 + n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Laufer)\n");
                        }
                    }
                    if (prufoutofbounds(x1 - n, y1 - n, 8) == 0) {
                        if (schachbrett[x1 - n][y1 - n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Laufer)\n");
                        }
                    }
                }
            }
            if(schachbrett[i][j] == 5) { //Suche Dame
                x1D=i;
                y1D=j;
                //Prüf Dame schwarz
                for(int n=0; n<8; n++) {
                    if (prufoutofbounds(x1D + n, y1D + n, 8) == 0) {
                        if (schachbrett[x1D + n][y1D + n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D + n, y1D - n, 8) == 0) {
                        if (schachbrett[x1D + n][y1D - n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D - n, y1D + n, 8) == 0) {
                        if (schachbrett[x1D - n][y1D + n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D - n, y1D - n, 8) == 0) {
                        if (schachbrett[x1D - n][y1D - n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                }
            }
        }
    }

    //Prüf Turm & Dame weiß
    fig = 0;
    for(int i=0; i<8; i++) { //Suche Turm
        for(int j=0; j<8; j++) {
            if(schachbrett[i][j] == 4) {
                x1T=i;
                y1T=j;
                for(int n=0; n<8; n++) {
                    if (prufoutofbounds(x1T + n, y1T, 8) == 0) {
                        if (schachbrett[x1T + n][y1T] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Turm)\n");
                        }
                    }
                    if (prufoutofbounds(x1T - n, y1T, 8) == 0) {
                        if (schachbrett[x1T - n][y1T] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Turm)\n");
                        }
                    }
                    if (prufoutofbounds(x1T, y1T + n, 8) == 0) {
                        if (schachbrett[x1T][y1T + n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Turm)\n");
                        }
                    }
                    if (prufoutofbounds(x1T, y1T - n, 8) == 0) {
                        if (schachbrett[x1T][y1T - n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Turm)\n");
                        }
                    }
                }
            }
            if(schachbrett[i][j] == 5) { //Suche Dame
                x1D=i;
                y1D=j;
                //Prüf Dame schwarz
                for(int n=0; n<8; n++) {
                    if (prufoutofbounds(x1D + n, y1D, 8) == 0) {
                        if (schachbrett[x1D + n][y1D] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D - n, y1D, 8) == 0) {
                        if (schachbrett[x1T - n][y1T] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D, y1D + n, 8) == 0) {
                        if (schachbrett[x1D][y1D + n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                    if (prufoutofbounds(x1D, y1D - n, 8) == 0) {
                        if (schachbrett[x1D][y1D - n] == -6) { //Überprüfung auf König Weiß
                            printf("Schach! (Dame)\n");
                        }
                    }
                }
            }
        }
    }

    //Prüf König weiß
    for(int i=0; i<8; i++) {
        for (int j = 0; j < 8; j++) {
            if (schachbrett[i][j] == 6) { //Suche König
                x1D = i;
                y1D = j;
                //Prüf König schwarz
                if (prufoutofbounds(x1 + 1, y1 + 1, 8) == 0) {
                    if (schachbrett[x1 + 1][y1 + 1] == -6) { //Überprüfung auf König Weiß
                        printf("Schach! (König)\n");
                    }
                }
                if (prufoutofbounds(x1 + 1, y1 - 1, 8) == 0) {
                    if (schachbrett[x1 + 1][y1 - 1] == -6) { //Überprüfung auf König Weiß
                        printf("Schach! (König)\n");
                    }
                }
                if (prufoutofbounds(x1 - 1, y1 + 1, 8) == 0) {
                    if (schachbrett[x1 - 1][y1 + 1] == -6) { //Überprüfung auf König Weiß
                        printf("Schach! (König)\n");
                    }
                }
                if (prufoutofbounds(x1 - 1, y1 - 1, 8) == 0) {
                    if (schachbrett[x1 - 1][y1 - 1] == -6) { //Überprüfung auf König Weiß
                        printf("Schach! (König)\n");
                    }
                }

                if (prufoutofbounds(x1 + 1, y1, 8) == 0) {
                    if (schachbrett[x1 + 1][y1] == -6) { //Überprüfung auf König Weiß
                        printf("Schach! (König)\n");
                    }
                }
                if (prufoutofbounds(x1 - 1, y1, 8) == 0) {
                    if (schachbrett[x1 - 1][y1] == -6) { //Überprüfung auf König Weiß
                        printf("Schach! (Dame)\n");
                    }
                }
                if (prufoutofbounds(x1, y1 + 1, 8) == 0) {
                    if (schachbrett[x1][y1 + 1] == -6) { //Überprüfung auf König Weiß
                        printf("Schach! (Dame)\n");
                    }
                }
                if (prufoutofbounds(x1, y1 - 1, 8) == 0) {
                    if (schachbrett[x1][y1 - 1] == -6) { //Überprüfung auf König Weiß

                        printf("Schach! (Dame)\n");
                    }
                }
            }
        }
    }
    return 0;
}

void spielzug(int (*schachbrett)[8], int grosse) {
    char x1temp;
    int x1, y1; //x1/y1 ist eine spielfigur
    char x2temp;
    int x2, y2; //wohin man möchte
    // ausgeben(schachbrett, grosse);
    //Abfrage des Spielzuges
    printf("Bitte geben Sie ein, welche Spielfigur Sie bewegen moechten (x,y):\n");
    scanf("%c,%d", &x1temp, &y1);
    fflush(stdin);
    switch (x1temp) {
        case 'A': x1 = 0; break;
        case 'B':
            x1 = 1;
            break;
        case 'C':
            x1 = 2;
            break;
        case 'D':
            x1 = 3;
            break;
        case 'E':
            x1 = 4;
            break;
        case 'F':
            x1 = 5;
            break;
        case 'G':
            x1 = 6;
            break;
        case 'H':
            x1 = 7;
            break;
        default:
            x1 = -1;
            break;
    }

    if ((pruffigur(y1, x1, schachbrett) == 1 || prufoutofbounds(y1, x1, grosse) == 1) || x1 == -1) {
        printf("%d, %d, %d\n", y1, x1, schachbrett[y1][x1]);
        spielzug(schachbrett, grosse);

    } else {
        printf("Wohin moechten Sie die Spielfigur bewegen (x,y)? \n");
        scanf("%c,%d", &x2temp, &y2);
        fflush(stdin);
        switch (x2temp) {
            case 'A':
                x2 = 0;
                break;
            case 'B':
                x2 = 1;
                break;
            case 'C':
                x2 = 2;
                break;
            case 'D':
                x2 = 3;
                break;
            case 'E':
                x2 = 4;
                break;
            case 'F':
                x2 = 5;
                break;
            case 'G':
                x2 = 6;
                break;
            case 'H':
                x2 = 7;
                break;
            default:
                x2 = -1;
                break;
        }
        if ((prufoutofbounds(y2, x2, grosse) == 1) || x2 == -1) {
            spielzug(schachbrett, grosse);

        } else {

            int dummy1 = 0;
            int dummy2 = 0;
            dummy1 = x1;
            x1 = y1;
            y1 = dummy1;

            dummy2 = x2;
            x2 = y2;
            y2 = dummy2;

            //Berechnung von der Schrittgrosse n
            int n1 = y2 - y1;
            int n2 = x2 - x1;
            printf("x2: %d, y2: %d, position wohin gehen: %d\nn1: %d, n2: %d \n x1: %d , y1: %d\n", x2, y2,
                   schachbrett[x2][y2], n1, n2, x1, y1);
            spielfigur(schachbrett, grosse, n1, n2, x1, y1, x2, y2); // + Überprüfung

        }
    }

}

int Stellungsbewertung(int (*schachbrett)[8], int grosse){

    int Wert=0;

    //Überprüfung ob König schwarz (Gegner) geschlagen
    if(schachSK(schachbrett, grosse) >= 0){
        return 100000;//ist gut für uns wenn gegner, also schwarz, gecshlagen wird
    }

    //Überprüfung ob König weiß (Eigen) geschlagen
    if(schachWK(schachbrett, grosse) >= 0){
        return -100000;//ist nicht gut für uns wenn wir, also weiss, gecshlagen wird
    }

    //Stellung König - Distanz
    int posKx;
    int posKy;

    for (int y=0; y<8;y++) { //Position vom König schwarz
        for (int x=0; x<8;x++){
            if(schachbrett[y][x] == -6){
                posKx=x;
                posKy=y;
            }
        }
    }

    int zahl = 45;
    for(int n=1; n<8; n++) {

        //diagonalen prüfen
        if(prufoutofbounds((posKx + n), (posKy + n), grosse)==0){
            if(schachbrett[posKx + n][posKy + n] > 0) {
                Wert += zahl;
            }
        }
        if(prufoutofbounds((posKx + n), (posKy - n), grosse)==0){
            if(schachbrett[posKx + n][posKy - n] > 0) {
                Wert += zahl;
            }
        }
        if(prufoutofbounds((posKx - n), (posKy + n), grosse)==0){
            if(schachbrett[posKx - n][posKy + n] > 0) {
                Wert += zahl;
            }
        }
        if(prufoutofbounds((posKx - n), (posKy - n), grosse)==0){
            if(schachbrett[posKx - n][posKy - n] > 0) {
                Wert += zahl;
            }
        }

        //geraden Prüfen
        if(prufoutofbounds((posKx + n), (posKy), grosse)==0){
            if(schachbrett[posKx + n][posKy + n] > 0) {
                Wert += zahl;
            }
        }
        if(prufoutofbounds((posKx - n), (posKy), grosse)==0){
            if(schachbrett[posKx + n][posKy - n] > 0) {
                Wert += zahl;
            }
        }
        if(prufoutofbounds((posKx), (posKy + n), grosse)==0){
            if(schachbrett[posKx - n][posKy + n] > 0) {
                Wert += zahl;
            }
        }
        if(prufoutofbounds((posKx), (posKy - n), grosse)==0){
            if(schachbrett[posKx - n][posKy - n] > 0) {
                Wert += zahl;
            }
        }
        zahl -= 5;//gehen eine reihe weiter
    }
    return Wert;

}



//dummy spielbrett
//0. WER KANN ÜBERHAUPT GEHEN.->..nur für die die gehen können:
//wer kann schlagen
//Wenn keiner schalgen kann: beste Bewertung langgehen

//for {jede Spielfigur 1. Zug bewerten, nur die höchste Bewertung in Liste position 1 abspeichern}
// Besten 1. SPeilzug gehen
//Gegner berechnen-> schlechtester Zug
//for {nach dem 1. SPeilzug besten 2. Spielzug
// Gegner berechnen
// 3. Spielzug finden und speichern
//return den besten 1. (und auch gehen), rekursiver aufruf

//Rückwärts:
//Max: 3. Zug: weiß von allen Zügen bester Zug
//Min: 2. bester zug von weiß an schwarz übergeben, schwarz sucht besten Zug für sich selbst
//Max: 1. bester Zug von schwarz übergeben an weiß, weiß sucht besten zug für sich,
//übergibt koordinaten an main

int bewertung(int (*schachbrett)[8], int xa, int ya, int grosse){ //TODO müssen wir noch weiter bearbeiten
    int n1;
    int n2;
    for (int y=0; y < grosse; y++) { //spalten=y
        for (int x = 0; x < grosse; x++) { //zeilen=x
            if(schachbrett[x][y]==6) { //Suche König
                n1 = xa - x;
                n2 = ya - y;
            }
        }
    }
    /*  for(alle Spielzüge){

 bewertung=bewertungMinimax();


 if(bewertung>beste){
 beste=bewertung;

 }
 }
 return beste;
*/

}


int berechnen(int *zahl, int tiefe, int (*schachbrett)[8]){

    if(tiefe==3){
        //return bewertung(schachbrett, );-> TODO müssen wir noch weiter bearbeiten
    }

    else{
        berechnen(zahl, tiefe++, schachbrett);

    }


}



//B:100; L:300; S:350; T:500; Dame:900; K:100000
void MinMax(int (*schachbrett)[8], int grosse) {

    int bew = INT_MIN;
    int tiefe = 0;
    //for(mögliche Züge: 2.)

    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 8; k++) {
            if (schachbrett[i][k] > 0) {
                switch (schachbrett[i][k]) {
                    case 1: //BauerW
                        //if(BauerW(schachbrett, n1, n2, x1, x2, y1, y2, grosse) == 0 ){
                            berechnen(&bew, tiefe, schachbrett);
                        //}
                        break;
                    case 2:

                        break;
                    case 3:

                        break;
                    case 4:

                        break;
                    case 5:

                        break;
                    case 6:

                        break;
                }
            }


        }
    }
}



//Position wieder auf null setzten
int main() {
    int grosse=8;
    int schachbrett[grosse][grosse];
    int schachnr = 1;
    initialisieren(schachbrett);
    ausgeben(schachbrett);
    //BewertungMinimax();
    int zahler = 0;// wenn gerade=weiß

   /* while(schachnr>=0){
        if((zahler % 2) == 0){  //Spielzug weiß
           //fkt w-> minmax//KI
        }else{       //Spielzug schwarz
            spielzug(schachbrett, grosse);//fkt sch
        }

        schachnr==schach(schachbrett);
        zahler++;
        ausgeben(schachbrett, grosse);

    }*/

    ausgeben(schachbrett);

//minmax mit schachbrett aufrufen;

    return 0;
}


