#include <stdlib.h>
#include <string.h>
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

void string_add_capacity(string *str, unsigned int additional_capacity) {
  str->capacity += additional_capacity;
  char *new_ptr = malloc(str->capacity);
  memcpy(new_ptr, str->ptr, str->capacity);
  free(str->ptr);
  str->ptr = new_ptr;
}

string *of_str(const char *str) {
  string *result = malloc(sizeof(string));
  result->size = strlen(str);
  result->capacity = result->size;
  result->ptr = malloc(sizeof(char)*result->capacity);
  memcpy(result->ptr, str, result->size);
  return result;
}

string *of_int(const int i) {
  string *result = malloc(sizeof(string));
  result->size = snprintf(NULL, 0, "%d", i);
  result->capacity = result->size+1;
  result->ptr = malloc(sizeof(char)*result->capacity);
  snprintf(result->ptr, result->capacity, "%d", i);
  return result;
}

void string_push(string *str, const char c) {
  if (str->size < str->capacity) {
    *(str->ptr+str->size) = c;
    str->size += 1;
  } else {
    string_add_capacity(str, str->capacity);
    string_push(str, c);
  }
}

void extend_string(string *destination, const string *source) {
  if (destination->capacity < destination->size + source->size) {
    string_add_capacity(destination, destination->size+source->size-destination->capacity);
  }
  memcpy(destination->ptr+destination->size, source->ptr, source->size);
  destination->size += source->size;
}

void ensure_compt(string *str) {
  if (str->size == 0 || *(str->ptr+str->size-1) != 0) {
    string_push(str, 0);
    str->size -= 1;
  }
}

void extend_of_str(string *destination, const char *source) {
  string *buffer = of_str(source);
  extend_string(destination, buffer);
  drop(buffer);
}

void print_string(string *str) {
  char *c_str = malloc(sizeof(char)*(str->size+1));
  memcpy(c_str, str->ptr, str->size);
  *(c_str+str->size) = 0;
  puts(c_str);
  free(c_str);
}

void drop(string *str) {
  free(str->ptr);
  free(str);
}
