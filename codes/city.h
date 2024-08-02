#ifndef _CIDADE_H_
#define _CIDADE_H_

#include "neighbor.h"
#include "vector.h"

typedef struct City City;

//Cria uma cidade com os parâmetros lidos do arquivo
City *city_construct(char *name, float x, float y, int n_neighbor, int idx);

//Adiciona um vizinho no vetor de vizinhos da cidade
void city_add_neighbor(City *c, Neighbor *n);

//Retorna a cidade no índice específico
City *get_city(Vector *c, int idx);

//Verifica o nome de duas cidades e vê se são iguais
int eq_name_city(void *c1, void *c2);

//Compara duas cidades e vê se elas são iguais
int cmp_cities(City *dest_city, City *current_city);

//Retorna o número de vizinhos que a cidade tem
int get_num_neighbor(City *c);

//Retorna o vetor de vizinhos da cidade
Vector *get_neighbor(City *c);

//Retorna o índice da cidade
int get_idx_city(City *c);

//Retorna a distância da cidade até a origem
float get_distance_origin(City *c);

//Retorna a distância heurística
float get_distance_heuristic(City *c);

//Atribui a distância da cidade até a origem à um atributo da estrutura
void set_distance_origin(City *c, float distance);

//Atribui a distância heurística da cidade até o destino à um atributo da estrutura
void set_distance_heuristic(City *current_city, City *dest_city);

//Imprime o nome da cidade
void print_name_city(City *c);

//Função de comparação para utilizar o algoritmo UCS
int cmp_min_path_ucs(void *a, void *b);

//Função de comparação para utilizar o algoritmo A*
int cmp_min_path_a_star(void *a, void *b);

//Desaloca a cidade
void city_destroy(City *c);

#endif