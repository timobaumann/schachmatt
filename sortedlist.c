#include <malloc.h>
#include "sorted.h"
#include "list.h"

SORTED* sorted_new() {
    return (SORTED*) list_new();
}

int sorted_size(SORTED* sl) {
    return list_size((LIST*) sl);
}

sorted_el* sorted_get(SORTED* sl, int index) {
    return (sorted_el*) list_get((LIST*) sl, index);
}

VALUE sorted_bisect_find(SORTED* sl, int key) {
    int left = 0;
    int right = sorted_size(sl);
    int index = left + ((right - left) / 2);
    while (sorted_get(sl, index)->key != key) {
        if (sorted_get(sl, index)->key < key) {
            right = index;
        } else {
            left = index;
        }
        index = left + ((right - left) / 2);
    }
    return sorted_get(sl, index)->value;
}

VALUE sorted_linear_find(SORTED* sl, int key) {
    int index = 0;
    while (index < sorted_size(sl)) {
        sorted_el* el = sorted_get(sl, index);
        if (el->key == key)
            return (el->value);
        index++;
    }
    return NULL;
}

VALUE sorted_find(SORTED* sl, int key) {
    return sorted_bisect_find(sl, key);
}

SORTED* sorted_insert(SORTED* sl, int key, VALUE value) {
    int index = 0;
    // soweit Liste durchlaufen bis wir an der richtigen Stelle sind
    while (index < sorted_size(sl) && sorted_get(sl, index)->key < key) {
        index++;
    }
    // zu speicherndes Element anlegen
    sorted_el* el = malloc(sizeof(sorted_el));
    el->key = key;
    el->value = value;
    // Element an die richtige Stelle legen
    sl = (SORTED*) list_insert_at((LIST*) sl,  index, (PAYLOAD) el);
    return sl;
}

void __sorted_el_printer(void* p) {
    sorted_el* el = (sorted_el*) p;
    printf("{key: %d, val: %p}", el->key, el->value);
}

void sorted_print(SORTED* sl) {
    list_print((LIST*) sl, &__sorted_el_printer);
}

