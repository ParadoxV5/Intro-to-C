#include <stdio.h>

// Fixed-width integers are a convenience from C99.
// They platform-dependently map the platform-dependent integer types to type aliases of explicit bit counts.
#include <inttypes.h> // Import additional integer types and macros

/* `inttypes.h` `#include`s `stdint.h`, which defines the following type aliases:
  |              Type(s)               | Signed/Unsigned Identifier | Min./Max. Signed/Unsigned Value  | Signed/Unsigned Literal Macro |
  |:----------------------------------:|:---------------------------|:---------------------------------|-------------------------------|
  | Exactly `#` bits *(not mandatory)* | ` `/`u` `int#_t`           | ` `/`U` `INT#_` `MIN`/`MAX`      |                               |
  |  Smallest type that has `#` bits   | ` `/`u` `int_least#_t`     | ` `/`U` `INT_LEAST#` `MIN`/`MAX` | ` `/`U` `INT#_C`              |
  |   Fastest type that has `#` bits   | ` `/`u` `int_fast#_t`      | ` `/`U` `INT_FAST#` `MIN`/`MAX`  |                               |
  | Type with as many bits as possible | ` `/`u` `intmax_t`         | ` `/`U` `INTMAX_` `MIN`/`MAX`    | ` `/`U` `INTMAX_C`            |
  |  Type with the size of a pointer   | ` `/`u` `intptr_t`         | ` `/`U` `INTPTR_` `MIN`/`MAX`    |                               |
*/
const uint64_t HEX = UINT64_C(0xFEDCBA9876543210);

/* `inttypes.h` also defines the following format text macro literals for the `printf` and `scanf` families:
  | Data Type              | `printf`/`scanf` `@` in `%@` |
  |:-----------------------|:-----------------------------|
  | ` `/`u` `int#_t`       | `PRI`/`SCN` `@#`             |
  | ` `/`u` `int_least#_t` | `PRI`/`SCN` `@LEAST#`        |
  | ` `/`u` `int_fast#_t`  | `PRI`/`SCN` `@FAST#`         |
  | ` `/`u` `intmax_t`     | `PRI`/`SCN` `@MAX`           |
  | ` `/`u` `intptr_t`     | `PRI`/`SCN` `@PTR`           |
*/
int main() {
  printf("%"PRIi64, HEX); // String literal concatenation: "Hello"", " "World""!" => "Hello, World!"
  printf(
    "\nintmax_t\t%" PRIiPTR "\t%" PRIiMAX "\t%" PRIiMAX "\t%" PRIuMAX,
           sizeof(intmax_t),   INTMAX_MIN,   INTMAX_MAX,  UINTMAX_MAX);
}
