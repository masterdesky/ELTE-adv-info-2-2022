#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>  // For `memset()`

#include "str.h"
#include "matrix.h"
#include "secure_io.h"
#include "operations.h"


void print_info(Matrix *m)
{
    fprintf(stderr, "--   TABLE INFO   --\n"
                    "--------------------\n");
    fprintf(stderr, "Rows: %zu, Cols: %zu\n\n", m->rows, m->cols);

    fprintf(stderr, "-- TABLE CONTENTS --\n"
                    "--------------------\n");
    for(size_t i = 0; i < m->rows; i++)
    {
        for(size_t j = 0; j < m->cols; j++)
        {
            fprintf(stderr, "%g\t", m->matrix[i*m->cols + j]);
        }
        fprintf(stderr, "\n");
    }
}


void evaluate_operations(Matrix *m)
{
    // Do operations
    double sum_t = sum_total(m);
    double *sum_r; sum_r = sum_rows(m);
    double *sum_c; sum_c = sum_cols(m);

    fprintf(stdout, "\n\nSum of vals:\n"
                    "----------------\n");
    fprintf(stdout, "SUM = [ %g ]", sum_t);


    fprintf(stdout, "\n\nSum of cols:\n"
                    "----------------\n");
    fprintf(stdout, "SUM = [ ");
    for(size_t i = 0; i < m->cols; i++)
    {
        fprintf(stdout, "%g ", sum_c[i]);
    }
    fprintf(stdout, "]");


    fprintf(stdout, "\n\nSum of rows:\n"
                    "----------------\n");
    fprintf(stdout, "SUM = [ ");
    for(size_t i = 0; i < m->rows; i++)
    {
        fprintf(stdout, "%g ", sum_r[i]);
    }
    fprintf(stdout, "]");
}


/*
The program will read in a file after asking for a file name. The file could
contain a table with a consistent delimiter and arbitrary number of columns and
rows.

The program will read these columns into an array and then sum all of them
by components. The shorter columns will be padded with zeros during summation
to match the length of the longest column.

*/
int main(int argc, char const *argv[])
{
    // Open the data file from STDIN
    FILE *fp = open_file();

    // Read in its contents to the `table` array
    Matrix m;
    size_t size = 16;
    malloc_mx(&m, size);
    secure_read_table(fp, &m);
    print_info(&m);

    // Evaluate some operations between the elements of the matrix
    evaluate_operations(&m);

    fclose(fp);
    free_mx(&m);
    return 0;
}
