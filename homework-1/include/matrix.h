// --------------------------------------------------------------------------//
//
//    Defines and handles matrixs with N elements.
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
    double *matrix;
    size_t size;
    size_t len;
    size_t rows, cols;
} Matrix;


void malloc_mx(Matrix *m, size_t size)
{
    m->size = size;
    m->rows = m->cols = m->len = 0;
    m->matrix = malloc(size * sizeof(m->matrix));
    if(!m->matrix)
    {
        fprintf(stderr, "Memory error! Cannot allocate memory for matrix!");
        exit(EXIT_FAILURE);
    }
}


void realloc_mx(Matrix *m, size_t size)
{
    m->size += size;    
    m->matrix = realloc(m->matrix, m->size * sizeof(m->matrix));
    if(!m->matrix)
    {
        fprintf(stderr, "Memory error! Cannot allocate memory for matrix!");
        exit(EXIT_FAILURE);
    }
}


void free_mx(Matrix *m)
{
    free(m->matrix);
    m->matrix = NULL;
    m->size = m->len = m->rows = m->cols = 0;
}