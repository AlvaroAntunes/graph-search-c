#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "city.h"
#include "constants.h"

//A cidade precisa guardar o distance_origin e distance_heuristic para fazer os cálculos de distância na utilização do UCS ou A*.
struct City {
    char name[TAM_NAME];
    float x, y;
    float distance_origin;
    float distance_heuristic;
    int n_neighbor;
    int idx;
    Vector *neighbor;
};

City *city_construct(char *name, float x, float y, int n_neighbor, int idx) {
    City *c = (City *)malloc(sizeof(City));

    strcpy(c->name, name);
    c->x = x;
    c->y = y;
    c->distance_origin = 0;
    c->distance_heuristic = 0;
    c->n_neighbor = n_neighbor;
    c->idx = idx;
    c->neighbor = vector_construct();

    return c;
}

void city_add_neighbor(City *c, Neighbor *n) {
    vector_push_back(c->neighbor, n);
}

City *get_city(Vector *c, int idx) {
    return (City *)vector_get(c, idx);
}

int eq_name_city(void *c1, void *c2) {
    City *city1 = (City *)c1;
    City *city2 = (City *)c2;

    if (!strcmp(city1->name, city2->name)) {
        return 1;
    }
    return 0;
}

//Para verificar se duas cidades são iguais, eu faço a verificação apenas do nome.
int cmp_cities(City *dest_city, City *current_city) {
    if (!strcmp(dest_city->name, current_city->name)) {
        return 1;
    }
    return 0;
}

int get_num_neighbor(City *c) {
    return c->n_neighbor;
}

Vector *get_neighbor(City *c) {
    return c->neighbor;
}

int get_idx_city(City *c) {
    return c->idx;
}

float get_distance_origin(City *c) {
    return c->distance_origin;
}

float get_distance_heuristic(City *c) {
    return c->distance_heuristic;
}

void set_distance_origin(City *c, float distance) {
    c->distance_origin = distance;
}

void set_distance_heuristic(City *current_city, City *dest_city) {
    current_city->distance_heuristic = sqrt(pow(dest_city->x - current_city->x, 2) + pow(dest_city->y - current_city->y, 2));
}

void print_name_city(City *c) {
    printf("%s\n", c->name);
}

int cmp_min_path_ucs(void *a, void *b)
{
    City *c1 = (City *)a;
    City *c2 = (City *)b;

    if (c1->distance_origin < c2->distance_origin) {
        return -1;
    }
    return 1;
}

int cmp_min_path_a_star(void *a, void *b) {
    City *c1 = (City *)a;
    City *c2 = (City *)b;

    if ((c1->distance_origin + c1->distance_heuristic) < (c2->distance_origin + c2->distance_heuristic)) {
        return -1;   
    }
    return 1;
}

void city_destroy(City *c) {
    if (c != NULL) {
        int size = c->n_neighbor;
        for (int i = 0; i < size; i++) {
            Neighbor *n = (Neighbor *)vector_pop_back(c->neighbor);
            neighbor_destroy(n);
        }
        vector_destroy(c->neighbor);
        free(c);
    }
}