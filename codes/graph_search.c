#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "graph_search.h"
#include "stack.h"

struct Frontier {
    void(*push)(void*,void*);
    void*(*pop)(void*);
    void(*frontier_destroy)(void*);
    int(*size_frontier)(void *);
    void *frontier;
};

Frontier *frontier_construct() {
    Frontier *f = (Frontier *)calloc(1, sizeof(Frontier));
    return f;
}

//Nessa função faço toda a busca no grafo, então a lógica geral do programa está aqui
void graph_search(int origin, int dest, Vector *cities, char *algorithm, int(*cmp_min_path)(void*, void*)) {
    Vector *visited = vector_construct();

    Frontier *f = frontier_construct();
    City *dest_city = get_city(cities, dest);

    if (!strcmp(algorithm, "DFS") || !strcmp(algorithm, "BFS")) {
        f->frontier = (void *)deque_construct();
        f->push = bfs_dfs_push;
        f->frontier_destroy = bfs_dfs_destroy;
        f->size_frontier = bfs_dfs_size;

        if (!strcmp(algorithm, "DFS")) {
            f->pop = dfs_pop;
        }
        else {
            f->pop = bfs_pop;
        }
    }
    else if (!strcmp(algorithm, "UCS") || !strcmp(algorithm, "A*")) {
        f->frontier = (void *)heap_constructor(cmp_min_path);
        f->push = a_star_ucs_push;
        f->pop = a_star_ucs_pop;
        f->frontier_destroy = a_star_ucs_destroy;
        f->size_frontier = a_star_ucs_size;
    }

    //Começarei com a cidade de origem, por isso faço essa inserção na fronteira.
    f->push(f->frontier, vector_get(cities, origin));

    int num_cities = vector_size(cities);
    int parent[num_cities]; //Esse vetor é utilizado para recuperar o caminho percorrido até uma certa cidade.
    float distances[num_cities]; //Esse vetor guarda a distância de uma cidade até o seu pai.
    for (int i = 0; i < num_cities; i++) { //Aqui faço a inicialização dos dois vetores.
        parent[i] = -1;
        distances[i] = 0;
    }
    
    int dest_found = 0;

    while (f->size_frontier(f->frontier) > 0) { //Procuro a cidade de destino enquanto a fronteira tem alguma cidade.
        City *current_city = f->pop(f->frontier);

        if (cmp_cities(dest_city, current_city)) {
            dest_found = 1;
            vector_push_back(visited, current_city);
            break;
        }
        else if (vector_find(visited, current_city, eq_name_city) != -1) {
            continue;
        } 
            
        int n_neighbor = get_num_neighbor(current_city);

        for (int i = 0; i < n_neighbor; i++) {
            int idx_neighbor = get_idx_neighbor(vector_get(get_neighbor(current_city), i)); //Pego o índice do vizinho no vetor de todas as cidades.
            float distance_neighbor = get_distance_neighbor(vector_get(get_neighbor(current_city), i)); //Pego a distância do vizinho até a cidade atual.
            City *neighbor_city = get_city(cities, idx_neighbor); //Pego a cidade que representa aquele vizinho.

            if (vector_find(visited, neighbor_city, eq_name_city) != -1) { //Se a cidade já foi visitada, eu não coloco ela na fronteira.
                continue;
            }

            else if (parent[idx_neighbor] != -1) {
                if (!strcmp(algorithm, "UCS") || !strcmp(algorithm, "A*")) {
                    float distance_old = get_distance_origin(get_city(cities, idx_neighbor)) + get_distance_heuristic(get_city(cities, idx_neighbor));
                    float distance_new = get_distance_origin(get_city(cities, get_idx_city(current_city))) + distance_neighbor + get_distance_heuristic(get_city(cities, idx_neighbor));

                    if (distance_old > distance_new) {
                            parent[idx_neighbor] = get_idx_city(current_city);
                            distances[idx_neighbor] = distance_neighbor; //Distância da cidade vizinha até o pai.
                    }
                }
            }
            else {
                parent[idx_neighbor] = get_idx_city(current_city);
                distances[idx_neighbor] = distance_neighbor; //Distância da cidade vizinha até o pai.
            }

            if (!strcmp(algorithm, "UCS") || !strcmp(algorithm, "A*")) {
                float distance_total = 0; //Essa distância é a distância da cidade até a origem.
                while (idx_neighbor != origin) {
                    distance_total += distances[idx_neighbor];
                    idx_neighbor = parent[idx_neighbor];
                }
                set_distance_origin(neighbor_city, distance_total); //Setando a distância da cidade até a origem.

                if(!strcmp(algorithm, "A*")) {
                    set_distance_heuristic(neighbor_city, dest_city); //Setando a distância heurística (distância euclidiana de duas cidades com coordenadas(x,y))
                }
            }
            f->push(f->frontier, neighbor_city);
        }
        vector_push_back(visited, current_city);
    }

    if (dest_found) {
        Stack *path = stack_constructor();
        float distance_total = 0;

        int current = dest;
        while (current != -1) { //Aqui eu recupero o caminho da cidade de destino até a origem, junto com o custo em KM.
            stack_push(path, get_city(cities, current));
            distance_total += distances[current];
            current = parent[current];
        }
        while (stack_size(path)) {
            City* city = (City *)stack_pop(path);
            print_name_city(city);
        }
        stack_destroy(path);

        printf("Custo: %.2f Num_Expandidos: %d\n", distance_total, vector_size(visited));
    } 
    else {
        printf("IMPOSSIVEL\n");
    }
    destroy_graph(cities, visited, f);
}

void bfs_dfs_push(void *frontier, void *item) {
    deque_push_back((Deque *)frontier, item);
}

void bfs_dfs_destroy(void *frontier) {
    deque_destroy((Deque *)frontier);
}

int bfs_dfs_size(void *frontier) {
    return deque_size((Deque *)frontier);
}

void *dfs_pop(void *frontier) {
    return deque_pop_back((Deque *)frontier);
}

void *bfs_pop(void *frontier) {
    return deque_pop_front((Deque *)frontier);
}

void a_star_ucs_push(void *frontier, void *item) {
    heap_push((Heap *)frontier, item);
}

void a_star_ucs_destroy(void *frontier) {
    heap_destroy((Heap *)frontier);
}

int a_star_ucs_size(void *frontier) {
    return heap_size((Heap *)frontier);
}

void *a_star_ucs_pop(void *frontier) {
    return heap_pop((Heap *)frontier);
}

//Primeiro desaloco todas as cidades do meu grafo, depois basta desalocar todas as estruturas utilizadas.
void destroy_graph(Vector *cities, Vector *visited, Frontier *f) {
    int size = vector_size(cities);

    for (int i = 0; i < size; i++) {
        City *c = (City *)vector_pop_back(cities);
        city_destroy(c);
    }
    vector_destroy(cities);
    vector_destroy(visited);
    f->frontier_destroy(f->frontier);
    free(f);
}