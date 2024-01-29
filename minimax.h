//
// Created by Anja Klosterhuber on 22.01.24.
//

#ifndef _MINIMAX_H
#define _MINIMAX_H

#include "list.h"

typedef void* ZUSTAND;

typedef LIST* (*nachfolgezustandsfunktion)(ZUSTAND z, int player);
typedef int (*zustandsbewertungsfunktion)(ZUSTAND z, int player);

ZUSTAND minimax(ZUSTAND schachbrett, int tiefe, int player, nachfolgezustandsfunktion, zustandsbewertungsfunktion);


#endif //_MINIMAX_H

