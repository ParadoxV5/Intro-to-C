#include <stdio.h>
#include <inttypes.h>

/* Allocated on the global memory – next to each other in this order
  (Address space layout randomization (ASLR) is a technique that shuffles addresses from their code layout,
  making it hard for hackers to calculate addresses off the code layout.
  For this demonstration, however, the locations of the following values must be consistent.)
*/
uint8_t array[] = {1, 2, 3, 4}; // size = 4
uint16_t splat = 0xBE1E; // Little-endian: 1E BE; Big-endian: BE 1E

int main() {
  printf("addresses:\tarray[0] @ %p\tarray[4] @ %p\ttail @ %p\n",
    array,
    &array[3],
    &splat
  );
  
  uint8_t i; // On the stack
  
  printf("before:");
  for(i = 0; i <= 4; ++i) // Intentional out-of-bounds read (note `<=` instead of `<`)
    printf("\t%"PRIX8, array[i]);
  //=> Little-endian: 1 2 3 4 1E ;  Big-endian: 1 2 3 4 BE
  array[--i] = 5; // Intentional out-of-bounds write
  printf("\n`splat` after:\t%"PRIX16"\t(ouch)\n", splat);
  //=> Little-endian: BE05 ;  Big-endian: 51E
  
  // Utilize `i` as a value on the stack
  puts("\nsmashing (0x10×) ...");
  for(i = 0; i < 0x10; ++i) { // Intentional *way* out-of-bounds write, loop until integer overflow
    printf("%"PRIX8"\t(was %"PRIX8" previously)\n", i, (&i)[i]); // (&i)[i] = *((&i) + i); (&i)[0] = *&i = i
    (&i)[i] = i;
  }
  /*=! prints 0x10 unknown numbers, the program then either:
    * gets killed by the stack protector
      * The stack protector is a feature in C compilers.
        It adds a bit of “stack canary” region at the end of the stack, and will know (but not prevent)
        that the program has smashed the stack if the value of this normally-inaccessible canary changed.
      * This mechanism is default off and enabled by the `-fstack-protector` flag,
        though modern Linuxes ships with a modded `gcc` with it
    * (seemingly) hangs for a bit and then segfault
      * There was no stack protection. In most architectures, right after the stack comes the return pointer.
        Consequences of it overwritten range from the program getting lost to arbitrary code execution (ACE).
  */
}
