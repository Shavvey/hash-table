#include <stdint.h>
#include <stdlib.h>

typedef struct {
  // Key part, important this doesn't change
  void *key; 
  uint32_t keylen;
  // Each item can include other stuff here...
  int value;
} Item;

/** Because we allow we closed addressing, 
 * each entry is a alist of items, not just one item */
typedef struct {
  size_t capacity;
  size_t size;
  Item *items;
} Entry;

/** HashTable data structure:
* Implementation uses `common.h`, for an alist of entries*/
typedef struct {
  const uint64_t NUMBUCKETS;
  Entry *entries;
} HashTable;

// API
uint32_t hash(const char *data, size_t len);
HashTable ht_new(const uint64_t NUMBUCKETS);
const Item *ht_lookup(const HashTable *ht, void *key, uint32_t keylen);
void ht_insert(HashTable *ht, Item item);
void ht_delete(HashTable *ht);
void ht_print(const HashTable *ht);
