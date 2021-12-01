#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct CString
{
    char* string;
    int length;
} CString;

CString* cstring_new(const char* str)
{
    CString* result = malloc(sizeof(CString));
    result->length = strlen(str) + 1; // include the \0 character
    result->string = malloc(result->length * sizeof(char));
    strcpy(result->string, str);
    return result;
}

int cstring_length(CString* cstring)
{
    return cstring->length;
}

char cstring_getchar(CString* cstring, int index)
{
    if (index >= cstring->length) return -1;
    return cstring->string[index];
}

int cstring_setchar(CString* cstring, int index, char c)
{
    if (index >= cstring->length) return -1;
    cstring->string[index] = c;
    return 0;
}

const char* cstring_getchars(CString* cstring)
{
    return cstring->string;
}

void cstring_free(CString* cstring)
{
    free(cstring->string);
    free(cstring);
}

int main()
{
    // tests
    CString* cstring = cstring_new("Ala ma kota.");
    assert(cstring_length(cstring) == 13);
    assert(cstring_getchar(cstring, 0) == 'A');
    assert(cstring_getchar(cstring, 1) == 'l');
    assert(cstring_getchar(cstring, 2) == 'a');
    cstring_setchar(cstring, 0, 'O');
    assert(cstring_getchar(cstring, 0) == 'O');
    assert(cstring_getchar(cstring, 100) == -1);

    cstring_free(cstring);
    return 0;
}
