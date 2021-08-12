/**
 * dstring.h
 *
 * A convinient wrapper around a char vector and includes some extra functionality
 *
 * NOTE: A string_t type can be passed in wherever there is a char* parameter,
 *          but a char* cannot be passed to a string_t parameter
 */

#ifndef CORE_CSTRING_H
#define CORE_CSTRING_H

#include "engine/core/base.h"

typedef char* string_t;

string_t    string_create(const char* c_str);
void        string_destroy(string_t str);

size_t      string_len(const string_t str);

void        string_cat(string_t str1, const string_t str2);
void        string_catc(string_t str1, const char* str2);
void        string_push(string_t str, char c);
void        string_copy(string_t dest, const string_t src);
int         string_cmp(const string_t str1, const string_t str2);

char*       string_find(const string_t big, const string_t little);
char*       string_findc(const string_t big, const char* little);
bool        string_replace(string_t str, const char* pattern, const char* with);

/** Returns a vector of strings, can be freed with vector_free */
char**      string_tok(const string_t str, const char* delims);

void        string_sprintf(string_t str, const char* fmt, ...);

void        string_to_upper(string_t str);
void        string_to_lower(string_t str);

uint32_t    string_hash(const string_t str);


#endif /* CORE_CSTRING_H */
