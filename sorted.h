#ifndef _SORTED_H
#define _SORTED_H
#include <stdio.h>

typedef void* VALUE;

typedef struct el {
    int key;
    VALUE value;
} sorted_el;

typedef struct LIST SORTED;

// create a new sorted list
SORTED* sorted_new();

// return the number of elements stored in the sorted list
int sorted_size(SORTED* s);

// get the element at a certain position from the sorted list
// → I'm a bit unhappy we made this part of the interface during class as it will be difficult to implement for
//   implementations that do not rely on a list for storing the values
sorted_el* sorted_get(SORTED* s, int index);

// find some element in the list based on the key
// if there is no such element, return NULL
VALUE sorted_find(SORTED* s, int key);

// insert a new value with a given key into the sorted list
SORTED* sorted_insert(SORTED* s, int key, VALUE value);

// print the sorted data in a format that represents the implementation used
void sorted_print(SORTED* s);

#endif
