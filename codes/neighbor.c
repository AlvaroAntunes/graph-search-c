#include <stdlib.h>
#include "neighbor.h"

struct Neighbor {
    int idx;
    float distance;
};

Neighbor *neighbor_construct(int idx, float distance) {
    Neighbor *n = (Neighbor *)malloc(sizeof(Neighbor));

    n->idx = idx;
    n->distance = distance;

    return n;
}

int get_idx_neighbor(Neighbor *n) {
    return n->idx;
}

float get_distance_neighbor(Neighbor *n) {
    return n->distance;
}

void neighbor_destroy(Neighbor *n) {
    if (n != NULL) {
        free(n);
    }
}