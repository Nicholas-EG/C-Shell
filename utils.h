#ifndef UTILS
#define UTILS

#include <stdlib.h>

#define SIZE 256

struct HashMap {
    char** map;
};

// Allocates and initializes a new HashMap
struct HashMap createHashMap();

// Frees all memory associated with the map and sets the pointer to NULL
void deleteHashMap(struct HashMap* map);

// Stores a copy of the value indexed by its first character
// Returns: 0 on success, 1 for invalid value, 2 for invalid map
int setMapValue(struct HashMap* map, const char* value);

#endif