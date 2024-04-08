#include <limits.h>
#include <stdlib.h>
#include <stdio.h>


// Same format as Java
/** Returns a `long` so it does not overflow. Though `unsigned`, the result never exceed `LONG_MAX`. */
unsigned long square(int number) {
  return ((long)number) * number;
}

/* A programmer can use pointer params to
  * Limit the immediate size of the args stack (e.g., when passing a collection)
  * Ask for memory regions that the function can write to;
    i.e., emulate output or in-out params, typically for multiple return values.
*/
/** `square` but using an in-out param. Writes the `square` to the param. Returns `true` on integer overflow. */
_Bool square2(int* number) {
  unsigned long sq = square(*number);
  *number = (int)sq;
  return sq > INT_MAX;
}


/*
  Array param must have known size (expected minimum, that is, since caller can point to whatever)
  Using the array as an output param (array identifiers are pointers after all)
  Note: Functions cannot return an array (what’d you do, `malloc`?)
*/
/** Backport `gets_s` (consumes rest of line; no constraint handler integration) */
char* ngets(size_t n, char str[n]) {
  if(n == 0)
    return NULL;
  str[n--] = '\0'; // '\0' termination
  
  int c;
  for(int i = 0; i < n; ++i) {
    c = getchar();
    if(c < '\0') // error
      return NULL;
    if(c == '\n')
      return str;
    str[i] = (char)c;
  }
  
  // Buffer overflow
  do c = getchar(); while(c != '\n' && c >= '\0');
  return NULL;
}


/* There are two signatures of the main function: `int main(int, char * [])` and `int main(void)`
  *  int  argc   = non-negative count of command-line args (yet can’t be `unsigned`)
  * char* argv[] = array of Strings
    * [0] -> "program.exe" (note: *can* be `NULL` or empty if the environment doesn’t support it.)
    * [1] -> "arg1"
    * [2] -> "arg2"
    * …
    * [argc] -> NULL
  */
int main(int argc, char* argv[]) {
  for(int i = 0; i < argc; ++i)
    puts(argv[i]);
  
  puts("Enter a number:");
  
  char input[64];
  if(ngets(64, input)) {
    int number = atoi(input);
    if(!square2(&number)) { // Pass by Reference
      printf("The square of your number is (%i)\n", number);
      return EXIT_SUCCESS; // `0` and `EXIT_SUCCESS` (which may be `0` anyhow) means no errors.
    }
  }
  puts("Your input exceeds range.");
  return EXIT_FAILURE; // Anything else means failure, though `EXIT_FAILURE` is available for consistency.
  
  // Implicit `return 0` __for `main` function only__ in C99+, undefined return otherwise.
}
