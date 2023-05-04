/*
  Preprocessor directives
  Preprocessor: a program run before the compiler itself (macros go brrr)
*/
#include <stdio.h> /* Replace this line with the contents of the C library `stdio.h` */
#define HELLO "Hello world\n" /* Replace all occurrences of `HELLO` with `"Hello world\n"` */

int main() { /* Main function */
  puts(HELLO);
  /* Exit code (0 = OK, not zero = error) */
  /*return 0;*/ /* implicit `return 0` **for `main` function only** */
}

/* More on libraries, functions, arrays and Strings later. */

// Oh yeah of course C has `//` for single-line comments.
// But C99 and newer only! Only `/*…*/` in Standard C!
