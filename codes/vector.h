
#ifndef _DATA_STRUCTURES_VECTOR_H_
#define _DATA_STRUCTURES_VECTOR_H_

typedef void* data_type;
typedef struct Vector Vector;

// Cria um vetor vazio
Vector *vector_construct();

// Adiciona um elemento no final do vetor
void vector_push_back(Vector *v, data_type val);

// Retorna o i-ésimo elemento do vetor
data_type vector_get(Vector *v, int i);

// Atribui o valor val ao i-ésimo elemento do vetor
void vector_set(Vector *v, int i, data_type val);

// Retorna o tamanho do vetor
int vector_size(Vector *v);

// Retorna o indice do primeiro elemento com valor val. Retorna -1 se nao encontrado.
int vector_find(Vector *v, data_type val, int (*equality)(data_type, data_type)); 

// Remove o i-ésimo elemento do vetor.
data_type vector_remove(Vector *v, int i); //Receber a função para desalocar o ponteiro removido

// Remove o primeiro elemento
data_type vector_pop_front(Vector *v); //Receber a função para desalocar o ponteiro removido

// Remove o ultimo elemento
data_type vector_pop_back(Vector *v); //Receber a função para desalocar o ponteiro removido

// Insere o elemento na i-esima posicao
void vector_insert(Vector *v, int i, data_type val);

// Troca os elementos das posições i e j (i vira j e j vira i)
void vector_swap(Vector *v, int i, int j);

// Ordena o vetor in-place (sem criar um novo vetor)
void vector_sort(Vector *v, int (*compare)(data_type, data_type));

// Retorna o indice de val usando busca binaria. Retorna -1 se nao encontrado.
int vector_binary_search(Vector *v, data_type val); //Receber a função de comparação

// Inverte o vetor in-place (sem criar um novo vetor)
void vector_reverse(Vector *v);

// Libera a memoria alocada para o vetor
void vector_destroy(Vector *v);

#endif