#include <stdlib.h>
#include <string.h>

#include "util.h"

#define SIZE 256

struct HashMap {
    char** map;
};

struct HashMap createHashMap() {
    struct HashMap map;
    map.map = (char**)calloc(SIZE, sizeof(char*));
    return map;
}

void deleteHashMap(struct HashMap* map) {
    if (!map || !map->map) return;

    for (int i = 0; i < SIZE; i++) {
        free(map->map[i]);
    }
    free(map->map);
    map->map = NULL;
}

int setMapValue(struct HashMap* map, const char* value) {
    if (value == NULL || *value == '\0') return 1;
    if (map->map == NULL) return 2;

    unsigned char index = (unsigned char)value[0];
    free(map->map[index]);
    map->map[index] = strdup(value);
    return 0;
}