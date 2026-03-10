#include "hash.h"
#include "common.h"

// Return positive remainder (e.g. -1modn => n-1)
static int mod(int a, int b) { return (a % b + b) % b; }

// NOTE: Naive hash function, maybe we could use a modified LFSR
uint64_t hash(char *data, size_t num_bytes, const uint64_t NUMBUCKETS) {
  // Do the hashing here
  register int hash;
  // NOTE: We don't do any bounds checking here,
  // we assume that the args we are given are "correct"
  for (size_t s = 0; s < num_bytes; s += 1) {
    hash = data[s] ^ hash;
  }
  return mod(hash, NUMBUCKETS);
}

HashTable ht_new(const uint64_t NUMBUCKETS) {
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
