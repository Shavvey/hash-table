#include "hash.h"
#include "common.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define FNV_OFFSET_BASIS 0x811C9DC5
#define FNV_PRIME 0x01000193

/** BASED_ON:
 * https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 */
uint32_t hash(const char *data, size_t len) {
  // NOTE: register keyword is a compilation hint to keep this value in a reg
  register uint32_t hash = FNV_OFFSET_BASIS;
  // Iterate accross pointer to bytes given
  for (; len > 0; len -= 1) {
    hash *= FNV_PRIME;
    hash ^= data[len];
  }
  return hash;
}

HashTable ht_new(const uint64_t NUMBUCKETS) {
  // NOTE: Limit the size of NUMBUCKETS
  if (NUMBUCKETS >= 1 << 31) {
    eprintf(
        "Number of entries in table should be less than 2^32 (4 million)\n");
    exit(1);
  }
  HashTable ht = (HashTable){
      .NUMBUCKETS = NUMBUCKETS,
      .entries = (Entry *)calloc(NUMBUCKETS, sizeof(Entry)),
  };
  if (ht.entries == NULL) {
    eprintf("Failed to allocate hash table with %lu entries!", NUMBUCKETS);
  }
  return ht;
}

const Item *ht_lookup(const HashTable *ht, void *key, uint32_t keylen) {
  uint32_t h = hash((char *)key, keylen);
  uint32_t idx = h % ht->NUMBUCKETS;
  Entry entry = ht->entries[idx];
  // If no chained together elements exist, just return the first one
  if (entry.size == 1)
    return &entry.items[0];
  for (size_t s = 0; s < entry.size; s += 1) {
    // NOTE: if key is allowed to be any data, we really should use strcmp
    if (strncmp(entry.items[s].key, (char *)key, keylen) == 0) {
      return &entry.items[s];
    }
  }
  // return null item
  return NULL;
}

void ht_insert(HashTable *ht, Item item) {
  uint32_t h = hash((char *)item.key, item.keylen);
  uint32_t idx = h % ht->NUMBUCKETS;
  Entry *e = ht->entries + idx;
  alist_append(e, item);
}

void ht_delete(HashTable *ht) {
  for (size_t s = 0; s < ht->NUMBUCKETS; s += 1) {
    alist_free(ht->entries + s);
  }
  free(ht->entries);
}

void ht_print(const HashTable *ht) {
  for (size_t s = 0; s < ht->NUMBUCKETS; s += 1) {
    if (ht->entries[s].size > 0) {
      // Get first item in table entry, to print out key!
      Item first = ht->entries[s].items[0];
      // NOTE: this assumes key only has ascii printable bytes, prob not true!
      printf("Key: %.*s => Values: (", first.keylen, (char *)first.key);
      Entry e = ht->entries[s];
      for (size_t r = 0; r < e.size; r += 1) {
        printf("%d ", e.items[r].value);
      }
      printf(")\n");
    }
  }
}
