#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "city.h"
#include "vector.h"
#include "neighbor.h"
#include "graph_search.h"

int main () {
    char path_arq[PATH_ARQ];
    scanf("%s", path_arq);
    getchar();

    FILE *arq = fopen(path_arq, "r");

    char algorithm[TAM_ALGORITHM];
    fscanf(arq, "%s\n", algorithm);

    int origin, dest;
    fscanf(arq, "%d %d\n", &origin, &dest);

    int n_cities;
    fscanf(arq, "%d", &n_cities);

    Vector *c = vector_construct();
    int idx_city = 0;

    while (n_cities > 0) {
        char name[TAM_NAME];
        float x, y;
        int n_neighbor;

        fscanf(arq, "\n%s %f %f %d", name, &x, &y, &n_neighbor);
        City *city = city_construct(name, x, y, n_neighbor, idx_city);

        for (int i = 0; i < n_neighbor; i++) { /*Leitura de todos os vizinhos de cada cidade (o vizinho possui distância até
                                                o pai e índice que ele está no vetor de todas as cidades).*/
            int idx;
            float distance;

            fscanf(arq, "%d %f", &idx, &distance);
            Neighbor *n = neighbor_construct(idx, distance);
            city_add_neighbor(city, n);
        }
        vector_push_back(c, city);
        n_cities--;
        idx_city++;
    }

    //Verifica qual será a função de comparação de rotas a depender do algoritmo escolhido (isso somente para o UCS e A*).
    int(*cmp_min_path)(void*, void*);
    
    if (!strcmp(algorithm, "UCS")) {
        cmp_min_path = cmp_min_path_ucs;
    }
    else {
        cmp_min_path = cmp_min_path_a_star;
    }

    graph_search(origin, dest, c, algorithm, cmp_min_path);
    fclose(arq);

    return 0;
} 