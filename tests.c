//
// Created by timo on 25.01.24.
//
#include <assert.h>
#include "schach.h"
#include "list.h"

int main() {
    BRETT* test = brett_cpy(triviales_brett);
    LIST* nachfolgezuege = list_new();
    Laeuferzug(test, 0, 0, 1, );
}