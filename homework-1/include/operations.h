// --------------------------------------------------------------------------//
//
//    Defines operations between matrix elements.
//
// --------------------------------------------------------------------------//


// -- Dependencies --
// (Convention for C headers to be self-contained)
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>


// -- Prototype declarations --
double sum_total(Matrix *m);
double* sum_rows(Matrix *m);
double* sum_cols(Matrix *m);


double sum_total(Matrix *m)
{
    double sum = 0;
    for(size_t i = 0; i < m->rows; i++)
    {
        for (size_t j = 0; j < m->cols; j++)
        {
            sum += m->matrix[i*m->cols + j];
        }
    }
    return sum;
}


double* sum_rows(Matrix *m)
{
    double *sum = malloc(m->rows * sizeof(m->matrix));
    memset(sum, 0, m->rows * sizeof(m->matrix));
    for(size_t i = 0; i < m->rows; i++)
    {
        for (size_t j = 0; j < m->cols; j++)
        {
            sum[i] += m->matrix[i*m->cols + j];
        }
    }
    return sum;
}


double* sum_cols(Matrix *m)
{
    double *sum = malloc(m->cols * sizeof(m->matrix));
    memset(sum, 0, m->cols * sizeof(m->matrix));
    for(size_t j = 0; j < m->cols; j++)
    {
        for (size_t i = 0; i < m->rows; i++)
        {
            sum[j] += m->matrix[i*m->cols + j];
        }
    }
    return sum;
}