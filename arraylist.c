// defines the ADT list using an array that may be increased or shrunk as necessary.
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

static const unsigned int ARRAYLIST_INITIAL_SIZE = 4;

typedef struct LIST {
    PAYLOAD* backing_array;
    unsigned int filled_size;
    unsigned int max_size;
} LIST;

/** create an empty list */
LIST* list_new() {
    LIST* l = malloc(sizeof(LIST));
    l->backing_array = NULL;
    l->max_size = 0;
    l->filled_size = 0;
    return l;
}

/** returns the current number of items stored in this list */
int list_size(LIST* l) {
    return (int) l->filled_size;
}

/** ensures that we can store one more PAYLOAD item in the backing array */
void ensure_space_available(LIST* l);

/** get the element of l at position i */
PAYLOAD list_get(LIST* l, unsigned int i) {
    assert(i < l->filled_size);
    return l->backing_array[i];
}

/** set the element of l at position i to p */
LIST* list_set(LIST* l, unsigned int i, PAYLOAD p) {
    assert(i < l->filled_size + 1);
    ensure_space_available(l);
    l->backing_array[i] = p;
    return l;
}

/** add at the end of the list */
LIST* list_append(LIST* l, PAYLOAD p) {
    ensure_space_available(l);
    l->backing_array[(l->filled_size)++] = p;
    return l;
}

LIST* list_insert_at(LIST* l, unsigned int index, PAYLOAD p) {
    assert(index <= l->filled_size && index >= 0);
    ensure_space_available(l);
    // make room
    for (unsigned int i = l->filled_size; i > index; i--) {
        l->backing_array[i] = l->backing_array[i - 1];
    }
    // put item
    l->backing_array[index] = p;
    l->filled_size++;
    return l;
}

bool list_contains(LIST* l, PAYLOAD p) {
    for (int i = 0; i < l->filled_size; i++) {
        if (l->backing_array[i] == p)
            return true;
    }
    return false;
}

int list_indexOf(LIST* l, PAYLOAD p) {
    for (int i = 0; i < l->filled_size; i++) {
        if (l->backing_array[i] == p)
            return i;
    }
    return -1;
}
/* wie praktisch, jetzt könnten wir list_contains ganz einfach so implementieren:
bool list_contains(LIST* l, PAYLOAD p) {
    return list_indexOf(l, p) != -1;
}
*/

LIST* list_remove(LIST* l, unsigned int i) {
    assert(i < l->filled_size);
    // free(l->backing_array[i]);
    for (unsigned int c = i; c < l->filled_size; c++) {
        l->backing_array[c] = l->backing_array[c + 1];
    }
    (l->filled_size)--;
    return l;
}

void list_free(LIST* l) {
    while (l->filled_size > 0) {
        l = list_remove(l, l->filled_size - 1);
    }
    if (l->backing_array != NULL) {
        free(l->backing_array);
    }
    free(l);
}

/** returns the maximum number of items that can currently be stored in this list */
int list_max_size(LIST* l) {
    return (int) l->max_size;
}

LIST* list_extend(LIST* l1, LIST* l2) {
    unsigned int l1_old_size = l1->filled_size;
    l1->filled_size += l2->filled_size;
    ensure_space_available(l1);
    memcpy(&(l1->backing_array[l1_old_size]), l2->backing_array, (l2->filled_size) * sizeof(PAYLOAD));
    return l1;
}

// for arraylist, there's no need for an implementation that is specifically tuned
void list_map(LIST* l, PAYLOAD (*func) (PAYLOAD)) {
    for (int i = 0; i < list_size(l); i++) {
        PAYLOAD p = list_get(l, i);
        PAYLOAD new_p = func(p);
        list_set(l, i, new_p);
    }
}

void ensure_space_available(LIST* l) {
    // check that there's some room left
    if (l->filled_size >= l->max_size) {
        unsigned int new_size = l->max_size == 0 ? ARRAYLIST_INITIAL_SIZE : l->max_size << 1; // double size, start with 4
        // attempt to re-alloc
        PAYLOAD* new_array = realloc(l->backing_array, new_size * sizeof(PAYLOAD));
        if (new_array) {
            //printf("successfully extended array\n");
            l->backing_array = new_array;
            l->max_size = new_size;
        } else {
            // allocate new
            new_array = calloc(new_size, sizeof(PAYLOAD));
            assert(new_array != NULL); // <- unable to acquire new memory :-|
            // copy elements
            memcpy(new_array, l->backing_array, l->max_size * sizeof(PAYLOAD));
            // dismiss old
            free(l->backing_array);
            l->backing_array = new_array;
            l->max_size = new_size;
            //printf("changed to new array\n");
        }
    }
}

// print the sorted data in a format that represents the implementation used
void list_print(LIST* l, void (*payload_printer) (PAYLOAD)) {
    assert (l != NULL && "pointer to list must not be NULL");
    printf("array-backed list with maximum capacity %d, filled with %d items. Array ist at %p.\nContent: [", l->max_size, l->filled_size, l->backing_array);
    for (int i = 0; i < list_size(l); i++) {
        payload_printer(list_get(l, i));
        if (i < list_size(l) - 1)
            printf(", ");
    }
    printf("]\n");
}