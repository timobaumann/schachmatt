// defines the ADT list
#include <stdbool.h>

#ifndef _LIST_H
#define _LIST_H

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

typedef void* PAYLOAD;

typedef struct LIST LIST;

LIST* list_new();

int list_size(LIST* l);

/** get the element at index i in L */
PAYLOAD list_get(LIST* l, unsigned int i);

/** set the element at index i to p (discarding whatever there was before) and return the list */
LIST* list_set(LIST* l, unsigned int i, PAYLOAD p);

/** add the item to the end of the list */
LIST* list_append(LIST* l, PAYLOAD p);

/** add the item at the defined position in the list (shifting the remaining elements to the right */
LIST* list_insert_at(LIST* l, unsigned int i, PAYLOAD p);

/** return true if PAYLOAD p is contained (somewhere) in the list l */
bool list_contains(LIST* l, PAYLOAD p);

/** return the index of PAYLOAD p in list l */
int list_indexOf(LIST* l, PAYLOAD p);

/** remove the element at index i from list l*/
LIST* list_remove(LIST* l, unsigned int i);

/** return the concatenation of l1 and l2 */
LIST* list_extend(LIST* l1, LIST* l2);

/** map the function func onto each element of the list */
void list_map(LIST* l, PAYLOAD (*func) (PAYLOAD));

void list_free(LIST* l);

// print the sorted data in a format that represents the implementation used
void list_print(LIST* l, void (*payload_printer) (PAYLOAD));

#endif
