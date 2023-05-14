#include <stdio.h>

#define put() puts("")

int main() {
  int i; // `for` loop counter
  
  // An array is actually just a pointer to a continuous section of memory
  int a[5]; // Uninitialized – possibly junk values!
  printf("Address of a[0]:\t%p\n", &a[0]);
  printf("Value of a:\t%p\n", a);
  for(i = 0; i < 5; ++i)
    printf("%i\t", a[i]);
  put();
  
  // Initialized
  int b[/*5*/] = {1, 22, 333, 4444, 55555};
  for(i = 0; i < 5; ++i)
    printf("%i\t", b[i]);
  put();
  // Under the hood
  int* p_end = b + 5;
  for(int* p = b; p < p_end; ++p)
    printf("%i\t", *p);
  put();
  // ptr[0] = *ptr; ptr[1] = *(ptr+1)
  // (Compiler auto-adjusts increment for the pointer type of `int`)
  
  /* Can’t do
  a = {420, 69}; // reassign entire array
  a = b; // (you are changing the pointer arent’cha)
  int c[] = b; // only takes `{…}`
  */
  
  // And strings are façade of char arrays. Arrays of `const char`s, more specifically.
  const char* immutable = "Immutable";
  printf("%c\t", *immutable); //=> I
  printf("%c\t", immutable[5]); //=> a
  //immutable[6] = 'B'; //=! compiler error
  char* also_immutable = "Also Immutable"; // well the pointer *is* pointing to a char
  printf("%c\t", also_immutable[5]); //=> I
  //also_immutable[6] = 'M'; //=! segfault
  char modifiable[] = "Modifiable"; // kinda like casted to an array of not-`const` chars
  printf("%c\t", modifiable[5]); //=> i
  modifiable[6] = 'A';
  puts(modifiable);
  
  // 2D_array[outer][inner]
  const char strings[][3] = {
    "123",
    {'a', 'b', 'c'}, // incomplete row
    'x', 'y', 'z', '&' // inner curly braces are just for show
  };
  for(i = 0; i < 4; ++i) {
    printf("\t%p\t", strings[i]);
    for (int j = 0; j < 3; ++j)
      printf("%c", strings[i][j]);
  }
  put();
  
  // Array × Pointer
  int* array_of_int_pointers[] = {a, b + 2, p_end - 1};
  for(i = 0; i < 3; ++i)
    printf("%i\t", *array_of_int_pointers[i]);
  put();
  int(* pointer_to_int_array)[] = &b;
  for(i = 0; i < 5; ++i)
    printf("%i\t", (*pointer_to_int_array)[i]);
  put();
}
