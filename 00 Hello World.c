/*
  Preprocessor directives
  Preprocessor: a program run before the compiler itself (macros go brrr)
*/
#include <stdio.h> /* Replace this line with the contents of the C library `stdio.h` */
#define HELLO "Hello world" /* Replace all occurrences of `HELLO` with `"Hello world\n"` */
/* `const` is an annotation on a variable. This here is not interested in a full-blown variable though. */

int main() { /* Main function */
  puts(HELLO);
  /* Exit code (0 = OK, not zero = error) */
  /*return 0;*/ /* implicit `return 0` __for `main` function only__ in C99+ */
}

/* More on libraries, functions, arrays and strings later. */

// Oh yeah of course C has `//` for single-line comments.
// But C99 and newer only! Only `/*…*/` in Standard C!
