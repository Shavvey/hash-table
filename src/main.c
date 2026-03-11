#include "hash.h"

int main() {
  HashTable ht = ht_new(15);
  ht_insert(&ht, (Item){.key = "Hello", .keylen = 5, .value = 3});
  ht_insert(&ht, (Item){.key = "XOR", .keylen = 3, .value = 10});
  // simulating collision
  ht_insert(&ht, (Item){.key = "Cole", .keylen = 4, .value = 69});
  ht_insert(&ht, (Item){.key = "Cole", .keylen = 4, .value = 420});
  ht_print(&ht);
  ht_delete(&ht);
  return 0;
}
