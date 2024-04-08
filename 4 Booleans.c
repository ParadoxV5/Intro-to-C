/*
  There are no booleans in the low-level language C.
  Instead, 0 (or anything with zero binary value) is falsy;
  any other value is truthy, though one typically use `1` for `true`.
*/

#include <stdio.h>
#include <inttypes.h>

/*
  In C23, `true` and `false` are built-in keywords.
  For versions before C23, it is typical that `true` & `false` or
  library-specific equivalents defined via preprocessors.
*/
#include <stdbool.h> // Import __C99+__ Booleans preprocessor

int main() {
  // `_Bool` is a __C99+__ integer type`. It can only hold 1 or 0 and automatically convert any non-0 to 1.
  printf("sizeof(_Bool) \t%zu\n", sizeof(_Bool));
  
  /*`stdbool.h` `#define`s:
    bool  _Bool
    true  1
    false 0
  */
   bool t = true ;
  _Bool f = false;
  printf("stdbool.h\tt=%hhu f=%hhu\n", t, f);
  
  // Fetch `true`/`false` off always-`true`/`false` conditions
  t = 2>=1;
  f = 1>=2;
  printf("Comparison\tt=%hhu f=%hhu\n", t, f);
  
  // A user-supplied OG C not-necessarily-Boolean to demonstrate interaction with `if`
  int x; scanf("%i", &x);
  
  if(x == 0) // false
    printf("This is how C checks for `false`\n");
  else if(x == 1) // strictly true
    printf("But this is not how to check for `true`\n");
  else // also true
    printf("Because `2` and others are also `true` (possible if not using `_Bool`, e.g., in Standard C)\n");
  
  if(x)
    printf("Instead of `x != 0`, one can utilize the language.\n");
  else/* if(!x)*/
    printf("Similarly, instead of `x == 0`, there’s logic.\n");
  /*else
    deadCode();*/
  printf("\n");
  
  /* Other flow-control toys available in C [TL;DR: like Java without `for(element: collection)`]
    * Ternary Operator `?:`
    * `switch`-`case`-`default` (`break` required or it falls through)
    * `while` & `do`-`while`
    * `for(initialize, check, increment)`
    * `break` & `continue` and `return`
    * ~~`goto`~~ (actually y’know what, fk this)
   */
  
  bool error_occurred = false;
  return error_occurred;
    // Well, exit code of `1` for any error is less descriptive than unique error codes but no error message.
}
