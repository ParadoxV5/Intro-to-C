// C has no seamless Error Handling mechanism.
#include <errno.h>
// It is also typical for library developers to designate a their own error reporting mechanism.

/** Built-in error codes:
  * `EDOM`: Domain error (input out of range)
  * `ERANGE`: Range error (output exceeds data type size)
  * `EILSEQ`: [C95] Illegal byte sequence (e.g., bad String encoding)
  * [Other implementation-specific (e.g., POSIX) codes with names that start with `E`]
  These error macros have implementation-defined (platform-dependent) `int` values.
*/
typedef int errno_t;
/**
  Raise 2 to the pointed power in-place.
  @param number
    Though both the input and output are never negative,
    the argument points to a signed number to check unsigned casting errors for callers.
  @return
    * 0 on complete success
    * `ERANGE` if the result exceeds the range of a signed int
    * `EDOM` if the power is negative (which would result in a fraction)
*/
errno_t exp2l_s(long* number) {
  errno_t err;
  if(*number >= 0) {
    if(*number <= sizeof(long) * 8 - 2) {
      *number = 1L << *number;
      return 0;
    }
    // Guaranteed to overflow
    err = ERANGE;
  } else // Negatives are not supported
    err = EDOM;
  *number = 0;
  return err;
}

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
int main() {
  
  // Use standard library to get a `long`
  puts("Enter a number:");
  char string[sizeof(long) * 3 + 2]; // Est. chars required
  fgets(string, sizeof(string), stdin);
  char* str_end;
  long number = strtol(string, &str_end, 10); // The `strto`s are the only ones that report `ERANGE`.
  
  // As I implied at the top, not every library report errors in codes.
  if(str_end == string) { // String not used in conversion
    fputs("Your input is not a number.\n", stderr);
    return EILSEQ; // `0` is the “no errors” code for both error codes and program exit codes.
  }
  
  // Most of standard library use the `int` (behind the macro) `errno` for reporting errors.
  if(errno == ERANGE) {
    fputs("Your input is *way* too long.\n", stderr); //XXX: EDOM
    return errno;
  }
  
  /*
    * `strerror(error)` return a String corresponding to the given `error` code.
      It is implementation’s choice whether this char pointer points to predefined memory or a reused buffer.
    * `perror(message)` prints to `stderr` the message followed by `": "`
      (unless the message is `NULL` or points to `\0` (e.g., empty string)),
      then `strerror(errno)` and finish with `'\n'`.
  */
  errno = exp2l_s(&number);
  perror(NULL);
  if(!errno) // `0` is both the “no errors” code and the only falsy value.
    printf("2 raised to the power of your number is\t%li\n", number);
  return errno;
  
}
