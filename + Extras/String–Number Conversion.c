// Caution: Check for conversion and other errors not included in this example.

// For string conversion functions
#include <stdlib.h>
// For `printf`/`scanf` & variants
#include <stdio.h>

#define STRATEGY(title) puts("\n"title);

int main() {
  puts("For each STRATEGY, enter a hexadecimal 'short' and then a 'float'.\n");
  unsigned short hx;
  float g;
  
  STRATEGY("printf/scanf") // What’s been used so far
  // That said, `scanf` does not report String–number conversion errors
  scanf("%hx %g", &hx, &g); // The space is here just to eat the first '\n'
  while(getchar() != '\n'); // Consume the second `\n`
  printf("%hx\t%g\n", hx, g);

  #define BUFFER_SIZE 50
  char string[BUFFER_SIZE];
  #define READ fgets(string, BUFFER_SIZE, stdin);
  
  STRATEGY("sprintf/sscanf") // Like `fprintf`/`fscanf`, but to/from a String
  // Neither does `sscanf` report conversion errors
  READ
  sscanf(string, "%hx", &hx);
  READ
  sscanf(string, "%g", &g);
  //sprintf(buffer, "%hx\t%g\n", hx, g);
  snprintf(string, BUFFER_SIZE, "%hx\t%g\n", hx, g); // New in C99
  puts(string);
  
  STRATEGY("`stdlib.h` functions")
  READ
  hx = (unsigned short)strtoul(string, NULL, 16); /*
    * Returns an `unsigned long`
      * `strtol` returns a `signed long`
      * The above two both has a `ll` variant for C99+ `long long`s
      * C99+ also has `strtoimax` and `strtoumax` for `u`/`intmax_t`
    * The second arg points to a pointer which will be set to point to the next char of last char parsed
      * May be `NULL` to ignore this feature
    * The third arg is the base
      * 2..36
      * Bases 8 and 16 may have `0` and `0x`/`0X` prefixes respectively
      * Can also use 0 to auto detect between bases 10, 16 or 8 from the prefixes
      * `atol` and `atoll` are equivalents for base 10 and `NULL` 2nd arg; `atoi` returns to `int`
  */
  READ
  g = strtof(string, NULL); /*
    * `f`, `d` and `ld` returns `float`, `double` and `long double` respectively
    * These three have the same pointer arg and does not take the base arg
    * The `f` and `ld` ones are new in C99
    * `atof(string)` is equivalent to `strtod(string, NULL)`
  */
  printf("%hx\t%g\n", hx, g); // There is no `strfroml` or etc.
}
