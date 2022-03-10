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


// -- Reading a single line of string from STDIN or from a file
char* _read_line(FILE* input)
{
    // Start length is 16 characters
    size_t size = 16;
    char* str = (char*) malloc(sizeof(*str) * size);
    if(!str) { return str; }

    int ch;
    size_t len = 0;
    while(EOF != (ch = fgetc(input)) && ch != '\n')
    {
        str[len++] = ch;

        // If maximum length is reached, expand `str` with 16 characters
        if(len == size)
        {
            size += 16;
            str = (char*) realloc(str, sizeof(*str) * size);
            if(!str) { return str; }
        }
    }
    str[len++] = '\0';

    return str;
}


// Check consistency of 

// Determining delimiter in a table file
char* find_delimiter(FILE* fp)
{
    // Read characters in file into a dynamic string
    size_t size = 16;
    char* str = (char*) malloc(sizeof(*str) * size);
    if(!str) { return str; }

    int ch;
    size_t len = 0;
    // This while loop in this case reads the first line of the input file
    

    // At this point the first line is read and written into the `str` variable
    // 

    return str;
}


// -- Reading values from a table file to a 2D array --
char* secure_table_str(FILE* fp, double** table)
{
    // Read characters in file into a dynamic string
    size_t size = 16;
    char* str = (char*) malloc(sizeof(*str) * size);
    if(!str) { return str; }

    int ch;
    size_t len = 0;
    while(EOF != (ch = fgetc(fp)))
    {
        str[len++] = ch;

        // If maximum length is reached, expand `str` with 16 characters
        if(len == size)
        {
            size += 16;
            str = (char*) realloc(str, sizeof(*str) * size);
            if(!str) { return str; }
        }

        // If delimiter or end-of-line is reached, then convert the current
        // string into a double, empty the `str` variable and continue.
        if(!isdigit(ch) && ch != '.')
        {
            // Also if end-of-line is reached, increase the 
        }
    }
    str[len++] = '\0';

    return str;
}