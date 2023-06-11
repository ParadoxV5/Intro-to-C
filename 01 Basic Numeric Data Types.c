#include <stdio.h>
#include <limits.h> // Max. and min.s for each basic numeric types, which are platform-dependent size
int main() {
  
  puts("\nsizeof()\n");
  // `sizeof(…)` returns an `size_t`, whose size is also platform-dependent 
  // `ssize_t` is signed version of `size_t` which is unsigned
  printf(      "short\t%llu\n", sizeof(     short ));
  printf(        "int\t%llu\n", sizeof(     int   ));
  printf(       "long\t%llu\n", sizeof(     long  ));
  printf(  "long long\t%llu\n", sizeof(long long  )); // New in C99
  printf(      "float\t%llu\n", sizeof(     float ));
  printf(     "double\t%llu\n", sizeof(     double));
  printf("long double\t%llu\n", sizeof(long double));
  printf(       "char\t%llu\n", sizeof(     char  ));
  // The word `int` is optional in integer types (except `int` itself ofc)
  
  puts("\nmin/max\n");
  printf("          short\t%hi \t%hi \t%hu \n",  SHRT_MIN,  SHRT_MAX,  USHRT_MAX);
  printf("          int  \t%i  \t%i  \t%u  \n",   INT_MIN,   INT_MAX,   UINT_MAX);
  printf("          long \t%li \t%li \t%lu \n",  LONG_MIN,  LONG_MAX,  ULONG_MAX);
  printf("     long long \t%lli\t%lli\t%llu\n", LLONG_MIN, LLONG_MAX, ULLONG_MAX);
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
  double sc2 = 4e2;  // Still a floating-point [`400.0` rather than `400`]
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
  printf(
    "\nprintf\ni=%i\td=%d\tu=%u\thi=%hi\tli=%li\tlli=%lli\thhi=%hhi\tc=%c\tp=%p\tLf=%Lf\n",
               i,    d,    u,    hi,     li,     lli,      hhi,      c,    p,    Lf
  );
}
