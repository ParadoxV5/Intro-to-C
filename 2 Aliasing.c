#include <stdio.h>

// The `#define` macro can replace just about any sequence of words
#define TAU 6.28 // `double` literal
#define alias variable // variable identifier
#define program main // function identifier
#define number long // type
#define positive unsigned number // `#define`-ception
#define immutable const // variable qualifier
immutable positive FUNNY_NUMBER = 69;
const number double PI = TAU / 2; // Simple replacement, however, have no restrictions and can have too much power.

/* The proper way to alias a type
  ✅ No misuse
  ✅ Compilation checks at alias declaration rather than usage(s)
  ✅ Handled uniquely by tools such as IDEs
*/
typedef int num; // `typedef <old> <new>;`
//typedef unsigned num num2; // Nope
const num ANSWER = 42;

// `#define` with parameter
#define square(n) n * n
#define diff(a, b) ((a >= b) ? a - b : b - a)

int program() { // Similarly, unlike proper functions, the less-binary-size `#define doesn’t care about…
  // Types
  printf("%i\n", square(ANSWER)); //=> 1764
  printf("%lu\n", square(FUNNY_NUMBER)); //=> 4761
  printf("%Lf\n", square(PI)); //=> 9.8596
  // Closure (“Clang-Tidy: Macro replacement list should be enclosed in parentheses”)
  printf("%lu\n", square(FUNNY_NUMBER - 9));
    // 69 - 9 * 69 - 9 = -561, rather than (69 - 9) * (69 - 9) = 3600
  // Argument passing
  int alias = 43;
  printf("%i\n", diff(--variable, ANSWER));
    // --[43] >= 42 -> --[42] - 42 = -1, rather than --[43] >= 42 -> --[43] - 42 = 0
}
