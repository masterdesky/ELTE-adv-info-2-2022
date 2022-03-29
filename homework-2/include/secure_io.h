#include <stdio.h>
#include <stdlib.h>


// -- Prototype declarations --
FILE* open_file();
char* secure_read_stdin();


// 
FILE* open_file()
{
    char *fname;
    fprintf(stdout, "\nEnter path to output file: ");
    fname = secure_read_stdin();

    FILE *fp = fopen(fname, "w+");
    if (fp == NULL)
    {
       fprintf(stderr, "Error opening file \"%s\"!\n", fname);
       exit(EXIT_FAILURE);
    }

    free(fname);
    return fp;
}


char* secure_read_stdin()
{
    // Read characters to a dynamic string. Starting size is `size` characters.
    String s;
    size_t size = 4;
    malloc_str(&s, size);

    int ch;
    while(EOF != (ch = fgetc(stdin)) && ch != '\n')
    {
        s.string[s.len++] = ch;

        // If maximum length is reached, expand `str` by `size` entries
        if(s.len == s.size) { realloc_str(&s, size); }
    }
    s.string[s.len++] = '\0';

    return s.string;
}


// Prints the (x,y) values and the calculated derivates to STDOUT
void print(double* input, size_t N)
{
    for(size_t i = 0; i < N; i++)
    {
        fprintf(stdout, "%g ", input[i]);
    }
    fprintf(stdout, "\n\n");
}