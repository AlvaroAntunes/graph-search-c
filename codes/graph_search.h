#ifndef _GRAPH_SEARCH_H_
#define _GRAPH_SEARCH_H_

#include "city.h"
#include "deque.h"
#include "heap.h"

typedef struct Frontier Frontier;

Frontier *frontier_construct();

//Faz a busca no grafo e verifica se o destino foi achado ou não
void graph_search(int origin, int dest, Vector *cities, char *algorithm, int(*cmp_min_path)(void*, void*));

void bfs_dfs_push(void *frontier, void *item);

void bfs_dfs_destroy(void *frontier);

int bfs_dfs_size(void *frontier);

void *dfs_pop(void *frontier);

void *bfs_pop(void *frontier);

void a_star_ucs_push(void *frontier, void *item);

void a_star_ucs_destroy(void *frontier);

int a_star_ucs_size(void *frontier);

void *a_star_ucs_pop(void *frontier);

//Desaloca todos os vetores e a fronteira
void destroy_graph(Vector *cities, Vector *visited, Frontier *f);

#endif