#include <inttypes.h>
#include <stdio.h>

/*
  C `union`s can use every syntax available to `struct`ures.
  
  The key difference is that, while `struct` members sit next to each other in parallel,
  `union` stacks its members on the same chunk of memory.
  Therefore, a `union` typically only has one usable member.
  
  Whereas `struct`s are for grouping relevant variables (with same or different types) together (X `AND` Y),
  `union`s are for wrapping variables (typically of different types)
  where the context makes only one applicable (b `OR` β).
*/
union MyUnion {
  uint16_t uint16[2];
  uint32_t uint32;
};
/* a `struct` with the same members for comparison */
struct MyStruct {
  uint16_t uint16[2];
  uint32_t uint32;
};

int main() {
  printf("sizeof(MyUnion): \t%zu\t(expected: %zu + paddings)\n", sizeof( union MyUnion ), sizeof(uint32_t));
  printf("sizeof(MyStruct):\t%zu\t(expected: %zu + paddings)\n", sizeof(struct MyStruct), sizeof(uint64_t));
  
  #define DEFAULT_VALUE 0x98765432
  union MyUnion my_union = {.uint32 = DEFAULT_VALUE};
  
  // Overwrite example 1: basic example
  my_union.uint16[0] = 0xFFFF;
  printf("%"PRIX32"\t", my_union.uint32); // not DEFAULT_VALUE
  
  // Overwrite example 2: simple yet safe(r) endian detector
  my_union.uint32 = DEFAULT_VALUE;
  switch(my_union.uint16[0]) {
    case 0x5432:
      puts("little-endian (most CPUs)");
      return 0;
    case 0x9876:
      puts("big-endian (network order)");
      return 0;
    default:
      printf("obscure byte order (%"PRIX16")\n", my_union.uint16[0]);
      return my_union.uint16[0];
  }
}
