// --------------------------------------------------------------------------//
//
//    Securely reads in strings from STDIN or from a table file. Dynamically
//    allocates memory for strings during the reading.
//
// --------------------------------------------------------------------------//

// -- Dependencies --
// (Convention for C headers to be self-contained)
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>


// -- Prototype declarations --
FILE* open_file();
char* secure_read_stdin();
char get_delimiter();
void secure_read_table(FILE* fp, Matrix *m);


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
        else if((delimiter == '\0'))
        {
            delimiter = ',';
            fprintf(stdout, "Defalut delimiter: -> , <-\n\n");
            break;
        }
        else
        {
            fprintf(stdout, "Custom delimiter: -> %c <-\n\n", delimiter);
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
void secure_read_table(FILE* fp, Matrix *m)
{
    // Get the delimiter in the data file
    char delimiter = get_delimiter();

    // Read characters to a dynamic string. Starting size is `size` characters.
    String s;
    size_t size = 4;
    malloc_str(&s, size);

    char ch;                   // `ch` stores the current character read from input
    char ch_prev = delimiter;  // `ch_prev` is used to handle 
    while(EOF != (ch = fgetc(fp)))
    {
        // If delimiter or EOL is reached, then convert the current string into
        // a double, empty the `str` variable and continue. Else continue
        // gathering the characters to the `s.string` variable. 
        if(ch == delimiter || ch == '\n')
        {
            // 1. case: Two delimiter is next to each other on the same line.
            // In this case a value is missing from the dataset and set to 0.0
            // by default.
            if((ch_prev == delimiter) && (ch == delimiter))
            {
                m->matrix[m->len++] = 0.0;
            }
            // 2. case: Trailing delimiter at the end of the line is reached.
            // In this case it gets simply ignored. (Just catching `else-if`.)
            else if((ch_prev == delimiter) && (ch == '\n')) { }
            // 3. case: Multiple EOL after each other is found.
            // In this case they get simply ignored. (Just catching `else-if`.)
            else if((ch_prev == '\n') && (ch == '\n')) { }
            // 4. (default) case: Convert the current number from `char*` to
            // `double` and write it to the table.
            else {
                m->matrix[m->len++] = atof(s.string);
            }

            // Reset index and the `str` variable
            free_str(&s);
            malloc_str(&s, size);
            
            // If maximum length is reached, expand `table` by `size` entries
            if(m->len == m->size) { realloc_mx(m, size); }
            // If EOL with values on line is reached, increase the line counter
            if((ch == '\n') && (ch_prev != '\n')) { m->rows++; }
        }
        else
        {
            s.string[s.len++] = ch;
            if(s.len == s.size) { realloc_str(&s, size); }
        }
        // `ch_prev` stores the previous character read from input
        ch_prev = ch;
    }

    // Calculate the number of columns after finished reading the input
    m->cols = m->len / m->rows;
}