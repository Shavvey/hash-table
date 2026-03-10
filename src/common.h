#ifndef INCLUDE_SRC_COMMON_H_
#define INCLUDE_SRC_COMMON_H_
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define eprintf(msg, ...) do {\
  fprintf(stderr, "%s:%d:%s() [ERROR]: " msg, __FILE__, __LINE__, __func__, ##__VA_ARGS__);\
}while(0)

#ifndef NOWARN

#define wprintf(msg, ...) do {\
  fprintf(stderr, "%s:%d:%s() [WARN]: " msg, __FILE__, __LINE__, __func__, ##__VA_ARGS__);\
}while(0)
#else
#define wprintf(...)
#endif

#define UNIMPLEMENTED(...)\
do {\
  printf("%s:%d [UNIMPLEMENTED]: %s", __FILE__, __LINE__, __VA_ARGS__);\
  exit(1);\
}while(0)

/* ARRAY LIST INTERFACE */

/* ArrayList (al) requires a few struct members to be implemented:
 * al = &struct{size_t capacity, size_t size, <type> *items, ...}
 *
 * al is a pointer to struct with at least three members visible:
 * capacity: The current allocation capacity of arraylist.
 *           When capacity == size, reallocation occurs by some def increment.
 * size: The current size of the arraylist (i.e. items is an [0, size-1] array
 *        of items). 
 * items: A pointer to an array of elements. This can be any type,
 * (so long as it is not a void * pointer).
 **/
#define AL_RESIZE_INC 1 << 3

#define alist_last(al) (al)->items[(al)->size-1]

#define alist_append(al, item) do {                                          \
  if ((al)->capacity - (al)->size == 0) {                                    \
    (al)->capacity += AL_RESIZE_INC;                                         \
    (al)->items = realloc((al)->items, (al)->capacity*sizeof(*(al)->items)); \
    assert((al)->items != NULL && "Array list alloc failed!\n");             \
  }                                                                          \
  (al)->items[(al)->size] = (item);                                          \
  (al)->size += 1;                                                           \
}while(0)

#define alist_free(al) do {                                                  \
 (al)->size = 0;                                                             \
 (al)->capacity = 0;                                                         \
 free((al)->items);                                                          \
}while(0)

#define alist_append_many(al, new_items, size) do {                          \
  size_t i = 0;                                                              \
  while(i < (size)) {                                                        \
     alist_append((al), (new_items)[i]);                                     \
     i++;                                                                    \
  }                                                                          \
}while(0)

#define alist_delete_at(al, idx) do {                                        \
  if ((idx) >= (al)->size) {                                                 \
    eprintf("Out of range!\n");                                              \
    break;                                                                   \
  }                                                                          \
  for (size_t i = (idx); i < (al)->size; i++) {                              \
       (al)->items[i] = (al)->items[i+1];                                    \
  }                                                                          \
  (al)->size--;                                                              \
}while(0)

#define alist_delete_last(al) do {                                           \
  (al)->size--;                                                              \
}while(0)

#define alist_insert_at(al, item, idx) do {                                  \
  if ((idx) >= (al)->size) {                                                 \
    eprintf("Out of range!\n");                                              \
    break;                                                                   \
  }                                                                          \
  alist_append((al), alist_last((al)));                                      \
  for (size_t s = (al)->size; s > idx; s--) {                                \
       (al)->items[s]  = (al)->items[s-1];                                   \
  }                                                                          \
  (al)->items[(idx)] = (item);                                               \
}while(0)

#endif  // INCLUDE_SRC_COMMON_H_
