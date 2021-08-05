#include "cengine/data/dstring.h"
#include "cengine/data/vector.h"
#include "cengine/core/memory.h"
#include "cengine/core/base.h" /* UNUSED macro */

#include <string.h>
#include <stdio.h>

static void string__cap(string_t str);

string_t
string_create(const char* c_str)
{
    string_t str = NULL;
    vector_init(str, strlen(c_str) + 1);
    memcpy(str, c_str, strlen(c_str));
    vector_push(str, '\0');
}

void
string_init(string_t str)
{
    vector_init(str, VECTOR__DEFAULT_SIZE);
}

void
string_destroy(string_t str)
{
    vector_free(str);
}

size_t
string_len(const string_t str)
{
    return vector_size(str);
}

void
string_cat(string_t str1, const string_t str2)
{
    vector_cat(str1, str2);
}

void
string_catc(string_t str1, const char* str2)
{
    size_t len = strlen(str2) + 1;
    char* tmp = vector_push_n(str1, len);

    tmp[len] = '\0';

    while (len--)
        tmp[len] = str2[len];
}

void
string_append(string_t str, const char c)
{
    /* remove the null terminator */
    UNUSED(vector_pop(str));

    vector_push(str, c);
    vector_push(str, '\0');
}

void
string_copy(string_t dest, const string_t src)
{
    vector_copy(dest, src);
    string__cap(dest);
}

int
string_cmp(const string_t str1, const string_t str2)
{
    return strcmp(str1, str2);
}

char*
string_find(const string_t big, const string_t little)
{
    return strstr(big, little);
}

char*
string_findc(const string_t big, const char* little)
{
    return strstr(big, little);
}

bool
string_replace(string_t str, const char* pattern, const char* with)
{
}

char* string_tok(const string_t str, const char* delims)
{
    return strtok(str, delims);
}

bool
string_sprintf(string_t str, const char* fmt, ...)
{
}

void
string_toupper(string_t str)
{
    vector_foreach(str, i, {
        str[i] -= 32
    });
}

void
string_tolower(string_t str)
{
    vector_foreach(str, i, {
        str[i] += 32
    });
}

static void
string__cap(string_t str)
{
    if (vector_last(str) != '\0')
        vector_push(str, '\0');
}
