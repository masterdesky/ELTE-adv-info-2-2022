// --------------------------------------------------------------------------//
//
//    Defines and handles dynamically allocated strings.
//
// --------------------------------------------------------------------------//


// -- Dependencies --
// (Convention for C headers to be self-contained)
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>


typedef struct
{
    char *string;
    size_t size;
    size_t len;
} String;


void malloc_str(String *s, size_t size)
{
    s->size = size;
    s->len = 0;
    s->string = malloc(size * sizeof(s->string));
    if(!s->string)
    {
        fprintf(stderr, "Memory error! Cannot allocate memory for string!");
        exit(EXIT_FAILURE);
    }
}


void realloc_str(String *s, size_t size)
{
    s->size += size;
    s->string = realloc(s->string, s->size * sizeof(s->string));
    if(!s->string)
    {
        fprintf(stderr, "Memory error! Cannot allocate memory for string!");
        exit(EXIT_FAILURE);
    }
}


void free_str(String *s)
{
    free(s->string);
    s->string = NULL;
    s->size = s->len = 0;
}