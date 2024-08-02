#ifndef _NEIGHBOR_H_
#define _NEIGHBOR_H_

typedef struct Neighbor Neighbor;

//Cria um vizinho com os parâmetros lidos do arquivo
Neighbor *neighbor_construct(int idx, float distance);

//Retorna o índice do vizinho nos dados de entrada (índice real)
int get_idx_neighbor(Neighbor *n);

//Retorna a distância do vizinho até o seu "pai"
float get_distance_neighbor(Neighbor *n);

//Desaloca o vizinho
void neighbor_destroy(Neighbor *n);

#endif