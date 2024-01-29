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
    BRETT* test = brett_cpy(&initiales_brett);
    print_brett(test);
    printf("test_print_brett: print_brett output must be assessed manually\n");
}

void test_strahlzuege() {
    BRETT* test = brett_cpy(&triviales_brett);
    LIST* nachfolgezuege = list_new();
    strahlzuege(test, 3, 4, 1, 1, WHITE, LAEUFER, nachfolgezuege);
    int i = 0;
    for (int x = 4, y = 5; x < GROESSE && y < GROESSE; x++, y++) {
        BRETT* b = list_get(nachfolgezuege, i);
        print_brett(b);
        assert((*b)[x][y] == LAEUFER);
        i++;
    }
    assert(list_size(nachfolgezuege) == i);
    printf("test_strahlzuege nach Süd-Ost erfolgreich");
    test = brett_cpy(&triviales_brett);
    nachfolgezuege = list_new();
    strahlzuege(test, 3, 4, -1, 1, WHITE, LAEUFER, nachfolgezuege);
    i = 0;
    for (int x = 2, y = 5; x >= 0 && y < GROESSE; x--, y++) {
        BRETT* b = list_get(nachfolgezuege, i);
        print_brett(b);
        assert((*b)[x][y] == LAEUFER);
        i++;
    }
    assert(list_size(nachfolgezuege) == i);
    printf("test_strahlzuege nach Süd-West erfolgreich");
}

void test_laeuferzuege() {
    BRETT* test = brett_cpy(&triviales_brett);
    LIST* nachfolgezuege = list_new();
    // the following is supposed to fail: there's no bishop on 0,0
    // laeuferzuege(test, 0, 0, WHITE, nachfolgezuege);
    // the following is supposed to fail: there's a bishop on 3,4, but it's the other color
    // laeuferzuege(test, 4, 3, BLACK, nachfolgezuege);
    // now, this should yield
    laeuferzuege(test, 3, 4, WHITE, nachfolgezuege);
    assert(list_size(nachfolgezuege) == 13 && "falsche Anzahl Nachfolgezustände");
    list_print(nachfolgezuege, &print_brett);
    printf("test_laeuferzuege: actual states must be assessed manually!!\n");
}

void test_schach_nachfolgezustaende() {
    BRETT* test = brett_cpy(&triviales_brett);
    LIST* nachfolgezustaende = schach_nachfolgezustaende(test, WHITE);
    LIST* laeufernachfolgezuege = list_new();
    laeuferzuege(test, 3, 4, WHITE, laeufernachfolgezuege);
    assert(list_size(nachfolgezustaende) == list_size(laeufernachfolgezuege));
    for (int i = 0; i < list_size(nachfolgezustaende); i++) {
        BRETT* b = (BRETT*) list_get(nachfolgezustaende, i);
        list_contains_eql(laeufernachfolgezuege, (void*) b, &brett_eql);
    }
    printf("test_schach_nachfolgezustaende: doesn't add more errors :-)\n");
}

void test_schachmatt() {
    BRETT* test = brett_cpy(&triviales_brett);
    assert(schach_matt(test, WHITE));
    assert(schach_matt(test, BLACK));
}
    /*{
    BRETT* test = brett_cpy(&schachmatt);
    LIST* nachfolgezustaende = schach_nachfolgezustaende(test, BLACK);
    LIST* laeufernachfolgezuege = list_new();
    damenzuege(test, 0,2, BLACK, laeufernachfolgezuege);
    assert(list_size(nachfolgezustaende) == list_size(laeufernachfolgezuege));
    for (int i = 0; i < list_size(nachfolgezustaende); i++) {
        BRETT* b = (BRETT*) list_get(nachfolgezustaende, i);
        list_contains_eql(laeufernachfolgezuege, (void*) b, &brett_eql);
    }
    printf("test_schachmatt: alles passt\n");
} */

int main() {
    test_equals();
    test_print_brett();
    test_strahlzuege();
    test_laeuferzuege();
    test_schach_nachfolgezustaende();
    test_schachmatt();
    return 0;
}