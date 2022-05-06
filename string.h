#include <stddef.h>

#ifndef __STRING_H__
#define __STRING_H__
typedef struct {
  size_t size;
  size_t capacity;
  char *ptr;
} string;

string *null_string();
string *new_string();
string *of_str(const char *);
string *of_int(const int);
void string_push(string *, const char);
void extend_string(string *, const string *);
void drop(string *);
void print_string(string *);
#endif
