#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct vector  {
    int* arr;
    size_t size;
    size_t capacity;
};

typedef struct vector vector;

vector* vector_create(size_t sz);
void vector_resize(vector* self, size_t sz);
int vector_insert(vector* self, size_t index, int value); //
int vector_erase(vector* self, size_t index); //
int vector_find(vector* self, int value); //
void vector_clear(vector* self);
void push_back(vector* self, int value);
void op_back(vector* self);
int get_element(vector* self, size_t index);
void set_element(vector* self, size_t index, int value);
void print_vector(vector* self);
void vector_reserve(vector* self, size_t capacity);
void vector_shrink(vector* self);
int get_size(vector* self);
int get_capacity(vector* self);
void vector_delete(vector* self);

#endif // VECTOR_H_INCLUDED
