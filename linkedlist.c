#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

typedef struct LIST {
    PAYLOAD p;
    LIST* next;
} LIST;

/** create an empty list */
LIST* list_new() {
    return NULL;
}

int list_size(LIST* l) {
    int length = 0;
    while (l != NULL) {
        length++;
        l = l->next;
    }
    return length;
}

PAYLOAD list_get(LIST* l, unsigned int i) {
    assert(list_size(l) > i);
    unsigned int c = 0;
    while (c < i) {
        l = l->next;
        c++;
    }
    return l->p;
}

LIST* list_set(LIST* l, unsigned int i, PAYLOAD p) {
    assert(list_size(l) > i);
    unsigned int c = 0;
    while (c < i) {
        l = l->next;
        c++;
    }
    l->p = p;
    return l;
}

LIST* list_append(LIST* l, PAYLOAD p) {
    if (l == NULL) {
        // if there's nothing there yet, then we create a node and return it
        l = malloc(sizeof(LIST));
        l->p = p;
        l->next = NULL;
    } else {
        // idea: otherwise, we append at the end (go to end and append)
        LIST* i = l;
        while (i->next != NULL) {
            i = i->next;
        }
        LIST* n = malloc(sizeof(LIST));
        n->p = p;
        n->next = NULL;
        i->next = n;
    }
    return l;
}

LIST* list_insert_at(LIST* l, unsigned int index, PAYLOAD p) {
    LIST* ret = l;
    LIST* new_el = malloc(sizeof(LIST*));
    new_el->p = p;
    if (index == 0) {
        new_el->next = l;
        ret = new_el;
    } else {
        for (int i = 0; i < index - 1; i++) {
            l = l->next;
        }
        new_el->next = l->next;
        l->next = new_el;
    }
    return ret;
}

bool list_contains(LIST* l, PAYLOAD p) {
    while (l != NULL) {
        if (l->p == p) {
            return true;
        }
    }
    return false;
}

int list_indexOf(LIST* l, PAYLOAD p) {
    int i = 0;
    while (l != NULL) {
        if (l->p == p) {
            return i;
        }
        i++;
        l = l->next;
    }
    return -1;
}

LIST* list_remove(LIST* l, unsigned int i) {
    assert(l != NULL);
    LIST* ret = l;
    // Spezialfall: erstes Element entfernen:
    if (i == 0) {
        ret = l->next;
        //free(l->p);
        free(l);
    } else { // sonst: weiter hinten liegende Elemente entfernen:
        for (int c = 0; c < i - 1; c++) {
            l = l->next;
        }
        assert(l->next != NULL); // stop people from removing elements beyond the end of the list
        LIST* rem = l->next;
        l->next = rem->next;
        //free(l->p);
        free(l);
    }
    return ret;
}

void list_free(LIST* l) {
    while (l != NULL) {
        l = list_remove(l, 0);
    }
}

LIST* list_extend(LIST* l1, LIST* l2) {
    // idea: first get last element of l1, then point that element's next to l2
    LIST* l = l1;
    while (l->next != NULL)
        l = l->next;
    l->next = l2;
    return l1;
}

// for linkedlist, it makes sense to loop with a while rather than the for loop from before. Simple, isn't it?
void list_map(LIST* l, PAYLOAD (*func) (PAYLOAD)) {
    while (l != NULL) {
        l->p = func(l->p);
        l = l->next;
    }
}

// print the sorted data in a format that represents the implementation used
void __list_print(LIST* l, void (*payload_printer) (PAYLOAD)) {
    if (l == NULL)
        printf("NULL");
    else {
        printf("{p: ");
        payload_printer(l->p);
        printf(", n: ");
        __list_print(l->next, payload_printer);
        printf("}");
    }
}

void list_print(LIST* l, void (*payload_printer) (PAYLOAD)) {
    __list_print(l, payload_printer);
    printf("\n");
}