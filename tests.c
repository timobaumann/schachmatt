//
// Created by timo on 25.01.24.
//
#include <assert.h>
#include "list.h"
#include "schach.h"
#include <stdio.h>

void test_print_brett() {
    BRETT* test = brett_cpy(triviales_brett);
    print_brett(test);
    printf("print_brett output must be assessed manually\n");
}

void test_laeuferzuege() {
    BRETT* test = brett_cpy(triviales_brett);
    LIST* nachfolgezuege = list_new();
    // the following is supposed to fail: there's no bishop on 0,0
    // laeuferzuege(test, 0, 0, 1, nachfolgezuege);
    // the following is supposed to fail: there's a bishop on 3,4, but it's the other color
    // laeuferzuege(test, 4, 3, -1, nachfolgezuege);
    // now, this should yield
    laeuferzuege(test, 4, 3, 1, nachfolgezuege);
    assert(list_size(nachfolgezuege) == 13 && "falsche Anzahl Nachfolgezustände");
    list_print(nachfolgezuege, &print_brett);
    printf("actual states must be assessed manually!!\n");
}

int main() {
    test_print_brett();
    test_laeuferzuege();
}