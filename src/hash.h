#include <stdint.h>
#include <stdlib.h>

typedef struct {
  int value; 
} Item;

/** Because we allow we open addressing, 
 * each entry is a alist of items, not just one item */
typedef struct {
  size_t capacity;
  size_t size;
  Item *items;
} Entry;

/** HashTable data structure:
* Implementation uses `common.h`, for an alist of entries*/
typedef struct {
  size_t capacity;
  size_t size;
  Entry *items;
  const uint64_t NUMBUCKETS;
} HashTable;

// API
uint64_t hash(char *data, size_t num_bytes, const uint64_t NUMBUCKETS);
HashTable ht_new(const uint64_t NUMBUCKETS);
Item *ht_lookup(const HashTable *ht, Item item);
