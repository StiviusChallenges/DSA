#include "vector.h"

vector* vector_create(size_t sz)
{
    if(sz == 0)
        printf("Size cannot be equal to 0"), exit(1);
    vector* new_vector = malloc(sizeof(struct vector));
    new_vector->arr = (int*)calloc(sz,sizeof(int));
    new_vector->size = sz;
    new_vector->capacity = sz;
    return new_vector;
}

void vector_resize(vector* self, size_t sz)
{
    if(self)
    {
        if(sz == self->size) return;
        if(sz > self->capacity)
        {
            int* temp_arr = (int*)calloc(self->size,sizeof(int));
            for(size_t i = 0; i != self->size; i++)
                temp_arr[i] = self->arr[i];
            self->capacity = sz * 2;
            if(self->arr) free(self->arr);
            self->arr = (int*)calloc(self->capacity,sizeof(int));
            for(size_t i = 0; i != self->size; i++)
                self->arr[i] = temp_arr[i];
            free(temp_arr);
        }
        else if(sz < self->size)
        {
            for(size_t i = sz; i != self->size; i++)
                self->arr[i] = 0;
        }
        self->size = sz;
    }
    else
        printf("Passed invalid vector"), exit(1);
}

void push_back(vector* self, int value)
{
    if(self)
    {
        if(self->size >= self->capacity)
        {
            int* temp_arr = (int*)calloc(self->size,sizeof(int));
            for(size_t i = 0; i != self->size; i++)
                temp_arr[i] = self->arr[i];
            self->capacity *= 2;
            if(self->arr) free(self->arr);
            self->arr = (int*)calloc(self->capacity,sizeof(int));
            for(size_t i = 0; i != self->size; i++)
                self->arr[i] = temp_arr[i];
            free(temp_arr);
        }
        self->size += 1;
        self->arr[self->size-1] = value;
    }
    else
        printf("Passed invalid vector"), exit(1);
}

void pop_back(vector* self)
{
    if(self)
    {
        if(self->size > 0)
        {
            self->arr[self->size-1] = 0;
            self->size -= 1;
        }
    }
    else
        printf("Passed invalid vector"), exit(1);
}

int get_element(vector* self, size_t index)
{
    if(self)
    {
        if(index > self->size-1)
            printf("Out of range"), exit(1);
        return self->arr[index];
    }
    else
        printf("Passed invalid vector"), exit(1);
}

void set_element(vector* self, size_t index, int value)
{
    if(self)
    {
        if(index > self->size-1)
            printf("Out of range"), exit(1);
        self->arr[index] = value;
    }
    else
        printf("Passed invalid vector"), exit(1);
}

void print_vector(vector* self)
{
    if(self)
    {
        for(size_t i = 0; i != self->size; i++)
            printf("%zu: %d\n", i, self->arr[i]);
    }
    else
        printf("Passed invalid vector"), exit(1);
}

int vector_insert(vector* self, size_t index, int value)
{
    if(self)
    {
        if(index > self->size-1)
            printf("Out of range"), exit(1);
        int* temp_arr = (int*)calloc(self->size+1,sizeof(int));
        for(size_t i = 0; i != index; i++)
            temp_arr[i] = self->arr[i];
        temp_arr[index] = value;
        for(size_t i = index; i != self->size+1; i++)
            temp_arr[i+1] = self->arr[i];
        if(self->arr) free(self->arr);
        if(self->size+1 >= self->capacity)
            self->capacity *= 2;
        self->arr = (int*)calloc(self->capacity,sizeof(int));
        for(size_t i = 0; i != self->size+1; i++)
            self->arr[i] = temp_arr[i];
        self->size += 1;
        free(temp_arr);
        return index;
    }
    else
        printf("Passed invalid vector"), exit(1);
}

int vector_erase(vector* self, size_t index)
{
    if(self)
    {
        if(index < 0 || index > self->size-1)
            printf("Out of range"), exit(1);
        int* temp_arr = (int*)calloc(self->size-1,sizeof(int));
        for(size_t i = 0; i != index; i++)
            temp_arr[i] = self->arr[i];
        for(size_t i = index; i != self->size-1; i++)
            temp_arr[i] = self->arr[i+1];
        if(self->arr) free(self->arr);
        self->arr = (int*)calloc(self->capacity,sizeof(int));
        for(size_t i = 0; i != self->size-1; i++)
            self->arr[i] = temp_arr[i];
        self->size -= 1;
        free(temp_arr);
        return index;
    }
    else
        printf("Passed invalid vector"), exit(1);
}

int vector_find(vector* self, int value)
{
    if(self)
    {
        for(size_t i = 0; i != self->size; i++)
            if(self->arr[i] == value)
                return i;
        return -1;
    }
    else
        printf("Passed invalid vector"), exit(1);
}

void vector_clear(vector* self)
{
    if(self)
    {
        for(size_t i = 0; i != self->size; i++)
            self->arr[i] = 0;
        self->size = 0;
    }
    else
        printf("Passed invalid vector"), exit(1);
}

void vector_reserve(vector* self, size_t capacity)
{
    if(self)
    {
        if(capacity <= self->capacity)
            printf("New capacity cannot be less than current capacity"), exit(1);
        int* temp_arr = (int*)calloc(self->size-1,sizeof(int));
        for(size_t i = 0; i != self->size; i++)
            temp_arr[i] = self->arr[i];
        if(self->arr) free(self->arr);
        self->capacity = capacity;
        self->arr = (int*)calloc(self->capacity,sizeof(int));
        for(size_t i = 0; i != self->size; i++)
            self->arr[i] = temp_arr[i];
        free(temp_arr);

    }
    else
        printf("Passed invalid vector"), exit(1);
}

void vector_shrink(vector* self)
{
    if(self)
    {
        if(self->size >= self->capacity) return;
        int* temp_arr = (int*)calloc(self->size-1,sizeof(int));
        for(size_t i = 0; i != self->size; i++)
            temp_arr[i] = self->arr[i];
        if(self->arr) free(self->arr);
        self->capacity = self->size;
        self->arr = (int*)calloc(self->capacity,sizeof(int));
        for(size_t i = 0; i != self->size; i++)
            self->arr[i] = temp_arr[i];
        free(temp_arr);

    }
    else
        printf("Passed invalid vector"), exit(1);
}

void vector_delete(vector* self)
{
    if(self->arr) free(self->arr);
    if(self) free(self);
}

int get_size(vector* self)
{
    if(self)
        return self->size;
    else
        printf("Passed invalid vector"), exit(1);
}

int get_capacity(vector* self)
{
    if(self)
        return self->capacity;
    else
        printf("Passed invalid vector"), exit(1);
}