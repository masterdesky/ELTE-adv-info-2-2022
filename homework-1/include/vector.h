// --------------------------------------------------------------------------//
//
//    Defines and handles vectors with N elements.
//
// --------------------------------------------------------------------------//


// -- Dependencies --
// (Convention for C headers to be self-contained)
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>


typedef struct
{
    double *vector;
    size_t size;
    size_t len;
    size_t rows, cols;
} Vector;


void malloc_vec(Vector *v, size_t size)
{
    v->size = size;
    v->rows = v->cols = v->len = 0;
    v->vector = malloc(size * sizeof(v->vector));
    if(!v->vector)
    {
        fprintf(stderr, "Memory error! Cannot allocate memory for vector!");
        exit(EXIT_FAILURE);
    }
}


void realloc_vec(Vector *v, size_t size)
{
    v->size += size;    
    v->vector = realloc(v->vector, v->size * sizeof(v->vector));
    if(!v->vector)
    {
        fprintf(stderr, "Memory error! Cannot allocate memory for vector!");
        exit(EXIT_FAILURE);
    }
}


void free_vec(Vector *v)
{
    free(v->vector);
    v->vector = NULL;
    v->size = v->len = v->rows = v->cols = 0;
}