// --------------------------------------------------------------------------//
//
//    Securely reads in file names and files from STDIN. Dynamically
//    allocates memory for strings that contain filenames.
//
// --------------------------------------------------------------------------//

// -- Dependencies --
// (Convention for C headers to be self-contained)
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


// -- Secure string reading from STDIN --
char* secure_stdin_str(FILE* stdin)
{
    // Start length is 16 characters
    size_t size = 16;
    char* str = (char*) malloc(sizeof(*str) * size);
    if(!str) { return str; }

    int ch;
    size_t len = 0;
    while(EOF != (ch = fgetc(stdin)) && ch != '\n')
    {
        str[len++] = ch;
        if(len == size)
        {
            // If maximum length is reached, expand `str` with 16 characters
            size += 16;
            str = (char*) realloc(str, sizeof(*str) * size);
            if(!str) { return str; }
        }
    }
    str[len++] = '\0';

    return str;
}