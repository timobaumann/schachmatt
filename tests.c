//
// Created by timo on 25.01.24.
//
#include <assert.h>
#include "list.h"
#include "schach.h"

int main() {
    BRETT* test = brett_cpy(triviales_brett);
    print_brett(test);
/*    LIST* nachfolgezuege = list_new();
    Laeuferzug(test, 0, 0, 1, nachfolgezuege);
    list_print(nachfolgezuege, &print_brett);
    */
}