#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "string.h"

string *null_string() {
  return malloc(sizeof(string));
}

string *new_string() {
  string *result = malloc(sizeof(string));
  result->size = 0;
  result->capacity = 1;
  result->ptr = malloc(sizeof(char));
  return result;
}

string *of_str(const char *str) {
  string *result = malloc(sizeof(string));
  result->size = strlen(str)+1;
  result->capacity = result->size;
  result->ptr = malloc(sizeof(char)*result->capacity);
  strncpy(result->ptr, str, result->size);
  return result;
}

string *of_int(const unsigned int i) {
  string *result = malloc(sizeof(string));
  result->size = (unsigned int)log10(i);
  result->capacity = result->size;
  result->ptr = malloc(sizeof(char)*result->capacity);
  sprintf(result->ptr, "%d", i);
  return result;
}

void string_push(string *str, const char c) {
  if (str->size < str->capacity) {
    *(str->ptr+str->size) = c;
    str->size += 1;
  } else {
    char *new_ptr = malloc(str->capacity * 2);
    strncpy(new_ptr, str->ptr, str->size);
    free(str->ptr);
    str->ptr = new_ptr;
    string_push(str, c);
  }
}

void extend_string(string *destination, const string *source) {
  for (int i = 0; i < source->size; i++) {
    string_push(destination, *(source->ptr+i));
  }
}

void drop(string *str) {
  free(str->ptr);
  free(str);
}
