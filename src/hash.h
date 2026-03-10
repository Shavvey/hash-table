#include <stdint.h>
#include <stdlib.h>

typedef struct {
  int value; 
} Item;

typedef struct {
  
} Entry;

typedef struct {
  size_t capacity;
  size_t size;
  Entry *entries;
} HashTable;

// API
uint64_t hash(char *data, size_t num_bytes);
