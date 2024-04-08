#include <stdio.h>
#include <limits.h> // Max. and min.s for each basic numeric types, which are platform-dependent size
#include <stdint.h> // Max. for `size_t`
int main() {
  
  puts("\nsizeof()\n");
  /* `sizeof(…)` returns the size in units of `sizeof(char)`.
    The return type is unsigned `size_t`, whose size is also platform-dependent. It has a signed version, `ssize_t`.
    As of C99, `s`/`size_t` are mandated to be at least 16bits with a corresponding `printf`-family prefix `z`.
    (See below for `printf` info)
  */
  printf(      "short\t%zu\n", sizeof(     short )); // at least 16bits
  printf(        "int\t%zu\n", sizeof(     int   )); // at least 16bits (typically 32); preferred integer type
  printf(       "long\t%zu\n", sizeof(     long  )); // ≥32bits
  printf(  "long long\t%zu\n", sizeof(long long  )); // ≥64bits; New in C99
  printf(      "float\t%zu\n", sizeof(     float )); // IEEE-754 binary32
  printf(     "double\t%zu\n", sizeof(     double)); // IEEE-754 binary64
  printf("long double\t%zu\n", sizeof(long double)); // IEEE-754 binary128
  printf(       "char\t%zu\n", sizeof(     char  )); // ≥8bits; meant more for text chars and less for codepoint numbers
  // The word `int` is optional in the above integer types (except `int` itself ofc)
  
  puts("\nmin/max\n");
  printf("          short\t%hi \t%hi \t%hu \n",  SHRT_MIN,  SHRT_MAX,  USHRT_MAX);
  printf("          int  \t%i  \t%i  \t%u  \n",   INT_MIN,   INT_MAX,   UINT_MAX);
  printf("          long \t%li \t%li \t%lu \n",  LONG_MIN,  LONG_MAX,  ULONG_MAX);
  printf("     long long \t%lli\t%lli\t%llu\n", LLONG_MIN, LLONG_MAX, ULLONG_MAX);
  printf("      s/size_t \tTBA \tTBA \t%zu \n",                         SIZE_MAX); // New in C99
  // `char`s *and char literals* are actually a façade of codepoint integers, y’know, and are sometimes used as bytes
  // `char` is the only one that does not have a `signed`/`unsigned` default defined
  printf("un/signed char \t%hhi\t%hhi\t%hhu\n", SCHAR_MIN, SCHAR_MAX,  UCHAR_MAX);
  printf("          char \t%hi \t%hi\t     \n",  CHAR_MIN,  CHAR_MAX);

  // Number Literals
  // Note: floating-point numbers don’t have `unsigned` versions. (The sign is part of their spec!)
  int    dec =   99;
  int    hex = 0xFF;
  int    oct =  077;
  //   int    bin = 0b11; // New in C23
  long   l   = -69u; // `u`/`U` suffix explicitly marks it unsigned.
  float  pi  = 3.14f; // Note the `f`/`F` suffix
  float  tau = 6.28; // A `double` casted into a `float`
  double e   = 2.72;
  long double phi = 1.62; // Up-casting is fine; down-casting tho can have unexpected consequences.
  double sci = 98.64e-1; // 98.64 × 10^(-1)
  double sc2 = 4e2; // Still a floating-point [`400.0` rather than `400`]
  double bpt = 0xAFp10; // (0xAF) × 2^(10) [C99 Hex floating-point]
  // [The `.0` is optional just like `4e2`’s. The exponent doubles as disambiguation with an `f`/`F` suffix.]
  printf(
      "\nLiterals test\nhex=%i\toct=%i\tl=%li\ttau=%f\tsci=%f\tbpt=%f\n",
      hex,    oct,    l,     tau,    sci,    bpt
  );
  // `l`/`L` and `ll`/`LL` suffixes also mark a literal `long` and `long long` respectively,
  //   specifically for numbers above `U`/`INT_MAX` or more precise than `double`.
  // The hex `0x`, hexadecimal and exponentiation letters are all case-insensitive.

  // `printf` is generally consistent with Java and Ruby. Special ones noted below:
            int   i = -50;
            int   d =  50; // `d` is equivalent to `i` for the `printf` family.
   unsigned int   u = -50; // u  = unsigned [note no i]; note the implicit underflow (-5 => INT_MAX - 4)
      short int  hi = -50; // h  = short (int) [“half”]
       long int  li = -50; // l  = long (int)
  long long int lli = -50; // ll = l l [okay.]
    signed char hhi = 'S'; // hh = h h [“quarter” – `char` as a number (byte)] (New in C99)
  unsigned char   c =  83; // c  = char [honor the façade]
          void*   p = &pi; // p  = pointer [more on this later]
    long double  Lf = tau; // L = long (double); assignment from existing value
          size_t zi = sizeof(size_t); // z = si`z`e; assignment from expression
  printf(
    "\nprintf\ni=%i\td=%d\tu=%u\thi=%hi\tli=%li\tlli=%lli\thhi=%hhi\tc=%c\tp=%p\tLf=%Lf\tzi=%zi\n",
               i,    d,    u,    hi,     li,     lli,      hhi,      c,    p,    Lf,     zi
  );
}
