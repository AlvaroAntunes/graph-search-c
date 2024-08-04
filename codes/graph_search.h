#ifndef _GRAPH_SEARCH_H_
#define _GRAPH_SEARCH_H_

#include "city.h"
#include "deque.h"
#include "heap.h"

typedef struct Frontier Frontier;

Frontier *frontier_construct();

//Faz a busca no grafo e verifica se o destino foi encontrado ou não.
void graph_search(int origin, int dest, Vector *cities, char *algorithm, int(*cmp_min_path)(void*, void*));

//Como a fronteira é genérica, preciso usar essas funções para push, pop, size e destroy.
void bfs_dfs_push(void *frontier, void *item);

void bfs_dfs_destroy(void *frontier);

int bfs_dfs_size(void *frontier);

void *dfs_pop(void *frontier);

void *bfs_pop(void *frontier);

void a_star_ucs_push(void *frontier, void *item);

void a_star_ucs_destroy(void *frontier);

int a_star_ucs_size(void *frontier);

void *a_star_ucs_pop(void *frontier);

int a_star_or_ucs(char *algorithm);

int bfs_or_dfs(char *algorithm);

int heap_find_frontier(void *frontier, void *city, int(*eq_name)(void*,void*));

int deque_find_frontier(void *frontier, void *city, int(*eq_name)(void*,void*));

void print_path(Vector *cities, int dest, float *distances, int *parent, int visited);

//Desaloca todos os vetores, as cidades e a fronteira.
void destroy_graph(Vector *cities, Vector *visited, Frontier *f);

#endif