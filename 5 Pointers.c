#include <stdio.h>
#include <inttypes.h>

// Dynamic Memory Allocation headers
//#include <malloc.h> // Non-standard (mostly-Linux) header with additional (non-standard) functions
#include <stdlib.h> // Standard C header, here using only one of multiple features
// The program compiles using either header, as they only declare, typically not define (functions).

int main() {
  int myInt = 5;
  int* p_myInt = &myInt; // Pointer to X = memory address of X
  uintptr_t a_myInt = (uintptr_t)p_myInt; // uintptr_t = unsigned integer the size of a pointer
  
  /*
    int* = pointer to int
    *ptr = get value at pointer
    &val = get pointer of variable
  */
  printf("Value:\tmyInt=%i *p_myInt=%i\n", myInt, *p_myInt);
  printf("Address:\t&myInt=%p p_myInt=%p\n", &myInt, p_myInt);
  printf("Address Value:\ta_myInt=%"PRIuPTR"\n", a_myInt);
  
  const size_t PTR_BYTES = sizeof(void*); // void = no idea about the return; void* = no idea about the pointer contents
  printf("\nPointer Size is %zu: I am running on a %"PRIuMAX"-bit computer.\n\n", PTR_BYTES, PTR_BYTES * 8);
  
  printf("Write via variable\t");
  ++myInt;
  printf("*p_myInt=%i\n", *p_myInt);
  
  printf("Write via pointer\t");
  ++*p_myInt; // `(*p_myInt)++`: Order of Operation: *p_myInt++ => *(p_myInt++) => Postfix-ticks pointer instead
  printf("myInt=%i\n", myInt);
  
  // Dynamic Memory Allocation
  char* name = malloc(100); // Ask for 100 bytes of memory off the heap (rather than the stack)
    intmax_t* age = malloc(sizeof(intmax_t)); // Ask for `sizeof(intmax_t)` bytes of memory
      /* Notes for `malloc`:
        * It *does not* initialize the memory to all 0s (“zero it”).
          * Since it’s not required in many use cases
          * Though the memory might happen to be all 0s already.
          * The sibling `calloc(num, size)`, which allocates `num × size` bytes for arrays, does.
        * It (and the other `alloc` functions) returns the special `NULL` pointer upon failure (e.g., out of memory)
          * Special treatment could be done; I skipped them here to let the program error in segfault on its own.
        * There are no specifications on what comes out when trying to `alloc` 0 bytes of memory.
      */
      printf("%"PRIiMAX"\n", *age); // Prints whatever value was previously in this memory space
      
      printf("Enter your name:\t");
      fgets(name, 100, stdin);
      printf("Enter your age:\t");
      scanf("%"SCNiMAX, age); // Note: pass by pointer
      printf("Your name is %s and your age is %"PRIiMAX"\n", name, *age);
        // Strings are actually pointers to `char` sequences; more on them *soon*
      // Also: `realloc(ptr, new_size)`:
      // Change an `alloc`ed memory’s size (copying the data to a new address if necessary)
    free(age); // Release the memory (kina like manual garbage collect)
  free(name);
  // `free(NULL)` does nothing, in case the `alloc`ed memory actually gave the `NULL` pointer.
  
  // Can also let the OS claim the program’s allocated heap.
  // Not a good practice though; `free()` can surface corruptions that contribute to memory leaks.
}
