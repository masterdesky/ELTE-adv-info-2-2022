// --------------------------------------------------------------------------//
//
//    Securely reads in strings from STDIN or from a table file. Dynamically
//    allocates memory for strings read in during the.
//
// --------------------------------------------------------------------------//

// -- Dependencies --
// (Convention for C headers to be self-contained)
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>


char* malloc_str(size_t size)
{
    char* str = (char*) malloc(sizeof(*str) * size);
    if(!str)
    {
        fprintf(stderr, "Memory error! Cannot allocate memory for string!");
        exit(EXIT_FAILURE);
    }

    return str;
}


char* realloc_str(char* str, size_t size)
{
    size = sizeof(str)/sizeof(str[0]) + size;
    str = (char*) realloc(str, sizeof(*str) * size);
    if(!str)
    {
        fprintf(stderr, "Memory error! Cannot allocate memory for string!");
        exit(EXIT_FAILURE);
    }
}


double* malloc_vec(size_t size)
{
    double* vec = (double*) malloc(sizeof(*vec) * size);
    if(!vec)
    {
        fprintf(stderr, "Memory error! Cannot allocate memory for vector!");
        exit(EXIT_FAILURE);
    }

    return vec;
}


double* realloc_vec(double* vec, size_t size)
{
    size = sizeof(vec)/sizeof(vec[0]) + size;
    vec = (double*) realloc(vec, sizeof(*vec) * size);
    if(!vec)
    {
        fprintf(stderr, "Memory error! Cannot allocate memory for vector!");
        exit(EXIT_FAILURE);
    }
}


char* secure_read_stdin(FILE* stdin)
{
    // Read characters to a dynamic string. Starting size is 16 characters.
    size_t size = 16;
    char* str = malloc_str(size);

    int ch;
    size_t len = 0;
    while(EOF != (ch = fgetc(stdin)) && ch != '\n')
    {
        str[len++] = ch;

        // If maximum length is reached, expand `str` with 16 characters
        if(len == size) { str = realloc_str(str, size); }
    }
    str[len++] = '\0';

    return str;
}


// -- Reading values from a table file to a 2D array --
void secure_read_table(FILE* fp, double** table, char* delimiter)
{
    // Read characters to a dynamic string. Starting size is 16 characters.
    size_t size = 16;
    char* str = malloc_str(size);

    int ch;
    int line_num_read = 0;
    size_t len = 0;
    size_t t_len = 0;
    while(EOF != (ch = fgetc(fp)))
    {
        // If maximum length is reached, expand `str` with 16 characters
        if(len == size) { str = realloc_str(str, size); }

        // If delimiter or EOL is reached, then convert the current
        // string into a double, empty the `str` variable and continue.
        if(ch == delimiter && ch == '\n')
        {
            // Convert the `str` to double and write it to the table
            *table[t_len++] = atof(str);
            if(t_len == size) { *table = realloc_vec(*table, size); }

            // Reset index and `str`
            len = 0;
            free(str);
            char* str = malloc_str(size);

            // Also if EOL is reached, increase the line counter
            if(ch == '\n') { line_num_read++; }
        }
        else
        {
            str[len++] = ch;
        }
    }
}