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

#include "str.h"
#include "vector.h"


char* secure_read_stdin()
{
    // Read characters to a dynamic string. Starting size is `size` characters.
    String s;
    size_t size = 16;
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


// -- Reading values from a table file to a 2D array --
char get_delimiter()
{
    // Ask for the delimiter. If nothing is given, ',' is assumed.
    char delimiter;
    while(1)
    {
        fprintf(stdout, "Enter the delimiter of the file "
                        "(first character matters only): ");
        delimiter = secure_read_stdin()[0];
        // Check whether chosen delimiter is correct
        if((delimiter == '-') || isdigit(delimiter))
        {
            fprintf(stderr,
                    "Delimiter can't be numeric or the character \"-\"!\n\n");
            continue;
        }
        else if(delimiter == '\n')
        {
            fprintf(stdout, "Defalut delimiter chosen: -> , <-\n\n");
            break;
        }
        else
        {
            fprintf(stdout, "Custom delimiter chosen: -> %c <-\n\n", delimiter);
            break;
        }
    }
    return delimiter;
}


/*
Reads a file that contains arbitrary many columns and arbitrary many elements
in each of these columns. The delimiter between each columns can be also
arbitrary except for numerals and the "-" minus sign. Depending on the case,
the "." or the "," symbol is used as a decimal separator and will be detected
automatically.

*/
void secure_read_table(FILE* fp, Vector *v)
{
    // Get the delimiter in the data file
    char delimiter = get_delimiter();

    // Read characters to a dynamic string. Starting size is `size` characters.
    String s;
    size_t size = 16;
    malloc_str(&s, size);

    char ch;                   // `ch` stores the current character read from input
    char ch_prev = delimiter;  // `ch_prev` is used to detect missing values
    while(EOF != (ch = fgetc(fp)))
    {
        // If delimiter or EOL is reached, then convert the current
        // string into a double, empty the `str` variable and continue.
        if(ch != delimiter && ch != '\n')
        {
            s.string[s.len++] = ch;
            if(s.len == s.size) { realloc_str(&s, size); }
        }
        else
        {
            // If the previous non-digit character is the same as the current
            // one, it means that there is a missing value between two delimiters
            if(ch_prev == ch && !isdigit(ch)) { v->vector[v->len++] = 0.0;}
            // Convert `str` from char* to double and write it to the table
            else { v->vector[v->len++] = atof(s.string); }
            // If maximum length is reached, expand `table` by `size` entries
            if(v->len == v->size) { realloc_vec(v, size); }

            fprintf(stdout, "%g\n", v->vector[v->len-1]);

            // Reset index and the `str` variable
            free_str(&s);
            malloc_str(&s, size);

            // If EOL is reached, increase the line counter
            if(ch == '\n') { v->rows++; }
        }
        // `ch_prev` stores the previous character read from input
        ch_prev = ch;
    }

    // Calculate the number of columns after finished reading the input
    v->cols = v->len / v->rows;
}