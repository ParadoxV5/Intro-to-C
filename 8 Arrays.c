#include <stdio.h>

int main() {
  // An array is actually just a pointer to a continuous section of memory
  int a[5]; // Uninitialized – possibly junk values!
  printf("Address of a[0]:\t%p\n", &a[0]);
  printf("Value of a:\t%p\n", a);
  for(int i = 0; i < 5; ++i)
    printf("%i\t", a[i]);
  puts("");
  
  // Initialized
  int b[/*5*/] = {1, 22, 333, 4444, 55555};
  for(int i = 0; i < 5; ++i)
    printf("%i\t", b[i]);
  puts("");
  // Under the hood
  int* p_end = b + 5;
  for(int* p = b; p < p_end; ++p)
    printf("%i\t", *p);
  puts("\n");
  // ptr[0] = *ptr; ptr[1] = *(ptr+1)
  
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
  char modifyable[] = "Modifyable"; // kinda like casted to an array of not-`const` chars
  printf("%c\t", modifyable[5]); //=> y
  modifyable[6] = 'A';
  puts(modifyable);
  
  // 2D_array[outer][inner]
  const char strings[][3] = {
    "123",
    {'a', 'b', 'c'}, // incomplete row
    'x', 'y', 'z', '&' // inner curly braces are just for show
  };
  for(int i = 0; i < 4; ++i) {
    printf("\t%p\t", strings[i]);
    for (int j = 0; j < 3; ++j)
      printf("%c", strings[i][j]);
  }
}
