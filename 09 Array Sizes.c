#include <stdio.h>
#include <inttypes.h>

int main() {
  int array[5];
  // sizeof(type[n]) = sizeof(type) × n
  size_t sizeof_array = sizeof(array), sizeof_int = sizeof(int);
  printf("sizeof(array)\t%"PRIuPTR"\n", sizeof_array);
  printf("sizeof(int)\t%"PRIuPTR"\n", sizeof_int);
  printf("count of array\t%"PRIuPTR"\n\n", sizeof_array / sizeof_int);
  
  int table[][3] = { 8, 7, 6, 5, 4, 3, 2, 1 };
  // Recall that an array is a pointer to a __contiguous__ sequence of memory
  size_t sizeof_table = sizeof(table), count_table = sizeof_table / sizeof_int;
  printf("sizeof(table)\t%"PRIuPTR"\n", sizeof_table);
  printf("total count of table\t%"PRIuPTR"\n[\t", count_table);
  for(int i = 0; i < count_table; ++i)
    printf("%i\t", // Choose One:
      //table[0][i]
      (*table)[i]
      //*((*table)+i)
    ); 
  puts("]"); //=> [ 8 7 6 5 4 3 2 1 0 ]
  
  // Sub-indexing and Endianness
  // (C has the union type for better sub-indexing – near end of intro)
  uint32_t abgr = 0x1234567;
  void* p = &abgr; // forgets what type it’s pointing at
  uint8_t* ptr = p; // and be told that it points to uint8_t
  printf("\nbefore:");
  for(int i = 0; i < /* 32/8 */ 4; ++i) {
    printf("\t%"PRIX8, ptr[i]);
    ptr[i] += i * 0x11 + 0x8;
  }
  //=> Little-endian (most CPUs):  67 45 23 1
  //=> Big-endian (network order): 1 23 45 67
  printf("\nafter:\t%"PRIX32"\n", abgr);
  //=> Little-endian (most CPUs): 3C4D5E6F
  //=> Big-endian (network order): 93C6FA2
}
