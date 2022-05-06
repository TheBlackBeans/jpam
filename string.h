#ifndef __STRING_H__
#define __STRING_H__
typedef struct {
  unsigned int size;
  unsigned int capacity;
  char *ptr;
} string;

string *null_string();
string *new_string();
string *of_str(const char *);
string *of_int(const unsigned int);
void string_push(string *, const char);
void extend_string(string *, const string *);
void drop(string *);
#endif
