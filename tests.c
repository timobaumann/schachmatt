//
// Created by timo on 25.01.24.
//
#include <assert.h>
#include "list.h"
#include "schach.h"
#include <stdio.h>

void test_equals() {
    BRETT* a = brett_cpy(&initiales_brett);
    BRETT* b = brett_cpy(&triviales_brett);
    assert(brett_cmp(a, b) != 0);
}

void test_print_brett() {
    BRETT* test = brett_cpy(&triviales_brett);
    print_brett(test);
    printf("test_print_brett: print_brett output must be assessed manually\n");
}

void test_laeuferzuege() {
    BRETT* test = brett_cpy(&triviales_brett);
    LIST* nachfolgezuege = list_new();
    // the following is supposed to fail: there's no bishop on 0,0
    // laeuferzuege(test, 0, 0, WHITE, nachfolgezuege);
    // the following is supposed to fail: there's a bishop on 3,4, but it's the other color
    // laeuferzuege(test, 4, 3, BLACK, nachfolgezuege);
    // now, this should yield
    laeuferzuege(test, 4, 3, WHITE, nachfolgezuege);
    assert(list_size(nachfolgezuege) == 13 && "falsche Anzahl Nachfolgezustände");
    list_print(nachfolgezuege, &print_brett);
    printf("test_laeuferzuege: actual states must be assessed manually!!\n");
}

void test_schach_nachfolgezustaende() {
    BRETT* test = brett_cpy(&triviales_brett);
    LIST* nachfolgezustaende = schach_nachfolgezustaende(test, WHITE);
    LIST* laeufernachfolgezuege = list_new();
    laeuferzuege(test, 4,3, WHITE, laeufernachfolgezuege);
    assert(list_size(nachfolgezustaende) == list_size(laeufernachfolgezuege));
    for (int i = 0; i < list_size(nachfolgezustaende); i++) {
        BRETT* b = (BRETT*) list_get(nachfolgezustaende, i);
        list_contains_eql(laeufernachfolgezuege, (void*) b, &brett_eql);
    }
    printf("test_schach_nachfolgezustaende: doesn't add more errors :-)\n");
}

int main() {
    test_equals();
    test_print_brett();
    test_laeuferzuege();
    test_schach_nachfolgezustaende();
    return 0;
}