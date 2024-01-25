#include "sorted.h"
#include <stdio.h>

void print_stats(SORTED* s) {
    printf("items in list: %d",
           sorted_size(s));
    fflush(stdout);
    if (sorted_size(s) > 0) {
        printf(", items in list: [ ");
        fflush(stdout);
        for (int i = 0; i < sorted_size(s); i++) {
            sorted_el* el = sorted_get(s, i);
            printf("{key: %d, value: %d} ", el->key, (int) el->value);
            fflush(stdout);
        }
        printf("]");
    }
    printf("\n");
    printf("in the implementation:\n---\n");
    sorted_print(s);
    printf("---\n");
}

int main(int argc, char* argv[]) {
    SORTED* sl = sorted_new();
    print_stats(sl);
    sl = sorted_insert(sl, 2, (void*) 2);
    print_stats(sl);
    sl = sorted_insert(sl, 1, (void*) 1);
    print_stats(sl);
    sl = sorted_insert(sl, 3, (void*) 3);
    print_stats(sl);
    sl = sorted_insert(sl, 0, (void*) 3);
    print_stats(sl);
    int key = 2;
    VALUE* el = sorted_find(sl, key);
    printf("unter %d ist %d gespeichert.\n", key, (int) el);

    // wenn Sie das folgende tun, dann wundern Sie sich bitte über garnichts!
    //sorted_el X = {100, 10};
    //sl = list_insert_at((LIST*) sl, 2, &X);
    //print_stats(sl);
}