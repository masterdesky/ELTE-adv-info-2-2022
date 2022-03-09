#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom header(s)
#include <secure_io.h>
#include <vector.h>


FILE* open_file()
{
    char *fname;
    fprintf(stdout, "\nEnter the file path: ");
    fname = secure_stdin_str(stdin);

    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
    {
       fprintf(stderr, "Error opening file \"%s\"!\n", fname);
       exit(EXIT_FAILURE);
    }

    free(fname);
    return fp;
}


void read_file(FILE* fp)
{
    
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
    // Read the two files from STDIN
    FILE *fp = open_file();

    fclose(fp);
    return 0;
}
