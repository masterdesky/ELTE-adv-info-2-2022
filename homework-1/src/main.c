#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "secure_io.h"

FILE* open_file()
{
    char *fname;
    fprintf(stdout, "\nEnter absolute file path or relative to WD: ");
    fname = secure_read_stdin();

    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
    {
       fprintf(stderr, "Error opening file \"%s\"!\n", fname);
       exit(EXIT_FAILURE);
    }

    free(fname);
    return fp;
}


/*
The program will read in a file after asking for a file name. The file should
be a TSV or CSV file with arbitrary number of column.

The program will read these columns into an array and then sum all of them
by components. The shorter columns will be padded with zeros during summation
to match the length of the longest column.

*/
int main(int argc, char const *argv[])
{
    // Open the data file from STDIN
    FILE *fp = open_file();

    // Read in its contents to the `table` array
    Vector v;
    size_t size = 16;
    malloc_vec(&v, size);
    secure_read_table(fp, &v);

    fprintf(stdout, "Rows: %zu, Cols: %zu", v.rows, v.cols);

    for(size_t i = 0; i < v.rows; i++)
    {
        for(size_t j = 0; j < v.cols; j++)
        {
            fprintf(stdout, "%g ", v.vector[i*v.rows + j]);
        }
        fprintf(stdout, '\n');                
    }

    fclose(fp);
    free_vec(&v);
    return 0;
}
