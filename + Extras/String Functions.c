#include <stdio.h>
#include <inttypes.h>

/* `string.h` declares various String or Array functions.
  * `strXXX`: for Strings, use null byte as string terminators
  * `strnXXX`: for Strings with known (max) lengths – better to protect from reading out of bounds
  * `memXXX`: for generic Arrays; requires a number of bytes arg to know where the bounds are
  * `…_s`: [new in C11] safe variants with errno output; generally adds a `str_size` or `dest_size` param
*/
#include <string.h>

/* `ctype.h` declares `tolower` & `toupper` and a handful of functions for checking a char’s type:
  * isalnum (alphanumeric)
  * isdigit
  * isalpha
  * islower
  * isupper
  * isxdigit (hexadecimal)
  * ispunct (punctuation)
  * isgraph (visible)
  * isprint (printing – `isgraph` or typography space)
  * isspace
  * isblank [new in C99]
  * iscntrl (control)
*/
#include <ctype.h>

int main() {
  char first_name[11];
  char last_name[11];
  char full_name[21];
  char* token;
  
  printf("Enter first name (max 10 chars):\t");
  fgets(first_name, 10, stdin);
  first_name[10] = 0; // Ensure null terminate
  printf("Enter last name (max 10 chars): \t");
  fgets(last_name, 10, stdin);
  last_name[10] = 0; // Ditto
  
  // Search
  token = strchr(first_name, '\n');
  *token = '\0'; // delete line break, turn it into null terminator
  *strchr(last_name, '\n') = '\0'; // ditto
  /* Also:
    * memchr(str, c, n)
    * strrchr(str, c): Search for last occurrence
    * strpbrk(str, str2): Search any char in second string
    * strstr(haystack, needle): Search an entire substring
    * strspn(str, str2): Count length of prefix made of only chars in second string
    * strcspn(str, str2): Count length of prefix made of no chars in second string
  */
  
  // Set
  memset(full_name, '\0', 20); // zero out
  
  // Three-Way Compare (negative return => str1 < str2; positive => str1 > str2)
  if(strcmp(first_name, last_name) == 0)
    puts("Your first and last names are the same?");
  /* Also:
    * strncmp(str1, str2, n)
    * memcmp(str1, str2, n)
  */
  
  // Copy
  strcpy(full_name, first_name);
  /* Also:
    * strncpy(dest, src, src_size)
    * memcpy(dest, src, src_size)
    * memmove(dest, src, src_size): Overlap-safe version of `memcpy`
  */
  
  // `ctype.h` demo
  if(isalpha(full_name[0]))
    full_name[0] = (char)toupper(full_name[0]); // ensure upper case
  else
    puts("Your name does not start with a letter?");
  
  // Concatenate
  strcat(full_name, " ");
  strcat(full_name, last_name);
  printf("Full name:\t%s\n", full_name);
  /* Also:
    * strncat(dest, src, src_size)
  */
  
  // Length
  printf(
    "%"PRIuPTR" bytes used out of %"PRIuPTR" bytes\n",
    strlen(full_name),
    sizeof(full_name) - 1
  );
  
  // Split by Separator
  const char delim[] = " "; // Not a substring separator – split by any char in delim array
  token = strtok(full_name, delim);
  while(token) {
    printf("%s\t", token);
    token = strtok(NULL, delim);
  }
  puts("Full name after tokenization:");
  for(int_fast8_t i = 0; i <= 20; ++i)
    printf("%02"PRIxFAST8" ", full_name[i]);
}

// * strerror(errno): Get error message for errno: 
// … and more
