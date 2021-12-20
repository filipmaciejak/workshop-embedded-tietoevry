#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct CString
{
    char* string;
    size_t length;
} CString;

CString* cstring_new(const char* str)
{
    CString* result = (CString*) malloc(sizeof(CString));
    if (result == NULL) return NULL;
    result->length = strlen(str) + 1; // include the \0 character
    result->string = malloc(result->length * sizeof(char));
    strcpy(result->string, str);
    return result;
}

int cstring_length(CString* cstring)
{
    if (cstring == NULL) return 0;
    return cstring->length;
}

char cstring_getchar(CString* cstring, int index)
{
    if (cstring == NULL) return '\0';
    if (index < 0 || index >= cstring->length) return '\0';
    return cstring->string[index];
}

int cstring_setchar(CString* cstring, int index, char c)
{
    if (cstring == NULL) return -1;
    if (index < 0 || index >= cstring->length) return -1;
    cstring->string[index] = c;
    return 0;
}

const char* cstring_getchars(CString* cstring)
{
    if (cstring == NULL) return NULL;
    return cstring->string;
}

void cstring_free(CString* cstring)
{
    if (cstring == NULL) return;
    free(cstring->string);
    free(cstring);
}

int main()
{
    // tests
    CString* cstring = cstring_new("Ala ma kota.");
    assert(cstring_length(cstring) == 13);
    assert(cstring_length(NULL) == 0);
    assert(cstring_getchar(cstring, 0) == 'A');
    assert(cstring_getchar(cstring, 1) == 'l');
    assert(cstring_getchar(cstring, 2) == 'a');
    assert(cstring_setchar(cstring, 0, 'O') == 0);
    assert(cstring_setchar(NULL, 0, 'O') == -1);
    assert(cstring_getchar(cstring, 0) == 'O');
    assert(cstring_getchar(cstring, 100) == '\0');
    assert(cstring_getchar(cstring, -100) == '\0');
    assert(cstring_getchar(NULL, 2) == '\0');

    cstring_free(cstring);
    return 0;
}
