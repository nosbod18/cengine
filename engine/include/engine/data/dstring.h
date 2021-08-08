/**
 * dstring.h
 *
 * @brief A convinient wrapper around a char vector and includes some
 *          extra functionality
 *
 * NOTE: A string_t type can be passed in wherever there is a char* parameter,
 *          but a char* cannot be passed to a string_t parameter
 */

#ifndef __DATA_DSTRING_H__
#define __DATA_DSTRING_H__

#include <stddef.h>
#include <stdbool.h>

typedef char* string_t;

string_t    string_create(const char* c_str);
void        string_init(string_t str);
void        string_destroy(string_t str);

size_t      string_len(const string_t str);

void        string_cat(string_t str1, const string_t str2);
void        string_catc(string_t str1, const char* str2);
void        string_append(string_t str, const char c);
void        string_copy(string_t dest, const string_t src);
int         string_cmp(const string_t str1, const string_t str2);

char*       string_find(const string_t big, const string_t little);
char*       string_findc(const string_t big, const char* little);
bool        string_replace(string_t str, const char* pattern, const char* with);
char*       string_tok(const string_t str, const char* delims);

void        string_sprintf(string_t str, const char* fmt, ...);

void        string_to_upper(string_t str);
void        string_to_lower(string_t str);


#endif /* __DATA_DSTRING_H__ */
