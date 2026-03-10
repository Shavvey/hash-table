#include "hash.h"
#include "common.h"

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

// Return positive remainder (e.g. -1modn => n-1)
static int mod(int a, int b) { return (a % b + b) % b; }

HashTable ht_new(const uint64_t NUMBUCKETS) {
  // NOTE: Limit the size of NUMBUCKETS
  if (NUMBUCKETS >= 1 << 31) {
    eprintf(
        "Number of entries in table should be less than 2^32 (4 million)\n");
    exit(1);
  }
  HashTable ht =
      (HashTable){.NUMBUCKETS = NUMBUCKETS,
                  .capacity = NUMBUCKETS,
                  .size = NUMBUCKETS,
                  .items = (Entry *)malloc(sizeof(Entry) * NUMBUCKETS)};
  if (ht.items == NULL) {
    eprintf("Table allocation of %lu entries failed!\n", NUMBUCKETS);
    // Just exit out if table allocation fails
    exit(1);
  }
  return ht;
}
