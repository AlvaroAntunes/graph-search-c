#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

struct Vector
{
    data_type *data;
    int size;
    int allocated;
};

Vector *vector_construct() {
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->data = (data_type *)malloc(sizeof(data_type));
    v->size = 0;
    v->allocated = 1;

    return v;
}

void vector_push_back(Vector *v, data_type val) {
    if (v->size >= v->allocated) {
        v->allocated *= 2;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }
    v->data[v->size] = val;
    v->size++;
}

data_type vector_get(Vector *v, int i) {
    if (i >= 0 && i < v->size) {
        return v->data[i];
    }
    exit(printf("Erro ao acessar a posicao %d no vetor\n", i));
}

void vector_set(Vector *v, int i, data_type val) {
    if (i >= 0 && i <= v->size) {
        v->data[i] = val;
    } else {
        printf("Erro ao adicionar um dado na posicao %d no vetor\n", i);
        exit(1);
    }
}

int vector_size(Vector *v) {
    return v->size;
}

int vector_find(Vector *v, data_type val, int (*equality)(data_type, data_type))
{
    for (int i = 0; i < v->size; i++) {
        if (equality(val, v->data[i])) {
            return i;
        }
    }
    return -1;
}

data_type vector_max(Vector *v) {
    data_type max = v->data[0];

    for (int i = 1; i < v->size; i++) {
        if (v->data[i] > max) {
            max = v->data[i];
        }
    }

    return max;
}

data_type vector_min(Vector *v) {
    data_type min = v->data[0];

    for (int i = 1; i < v->size; i++) {
        if (v->data[i] < min) {
            min = v->data[i];
        }
    }

    return min;
}

int vector_argmax(Vector *v) {
    int index = 0;
    data_type max = v->data[0];

    for (int i = 1; i < v->size; i++) {
        if (v->data[i] > max) {
            index = i;
            max = v->data[i];
        }
    }

    return index;
}

int vector_argmin(Vector *v) {
    int index = 0;
    data_type min = v->data[0];

    for (int i = 1; i < v->size; i++) {
        if (v->data[i] < min) {
            index = i;
            min = v->data[i];
        }
    }

    return index;
}
 
data_type vector_remove(Vector *v, int i) {

    if (i < v->allocated) {
        data_type element_remove = v->data[i];

        for(; i < v->size - 1; i++) {
            v->data[i] = v->data[i + 1];
        }
        v->size--;

        return element_remove;
    } else {
        printf("Indice de remocao invalido\n");
        exit(1);
    }

}

data_type vector_pop_front(Vector *v) {
    data_type element_pop = vector_remove(v, 0);

    return element_pop;
}

data_type vector_pop_back(Vector *v) {
    data_type element_back = vector_remove(v, v->size - 1);

    return element_back;
}

void vector_insert(Vector *v, int i, data_type val) {
    if (v->size == v->allocated) {
        v->allocated *= 2;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }

    for (int j = v->size; j > i; j--) {
        v->data[j] = v->data[j - 1];
    }
        v->data[i] = val;
        v->size++;
}

void vector_swap(Vector *v, int i, int j) {
    data_type aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}

void vector_sort(Vector *v, int (*compare)(data_type, data_type)) {
    int i, j, troca = 1;

    for (j = v->size - 1; (j >= 1) && (troca); j--) {
        troca = 0;
        for (i = 0; i < j; i++) {
            if (compare(v->data[i], v->data[i + 1]) > 0) {
                vector_swap(v, i, i + 1);
                troca = 1;
            }
        }
    }
}

int vector_binary_search(Vector *v, data_type val) {
    int low = 0, high = v->size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        data_type guess = v->data[mid];

        if (guess == val)
            return mid;
        
        else if (guess < val)
            low = mid + 1;
        
        else
            high = mid - 1;
    }

    return -1;
}

void vector_reverse(Vector *v) {
    int j, i = 0;

    for (j = v->size - 1; j > i; j--) {
        vector_swap(v, i, j);
        i++;
    }
}

void vector_destroy(Vector *v) {
    if (v != NULL) {
        if (v->data != NULL) {
            free(v->data);
        }
        free(v);
    }
}
