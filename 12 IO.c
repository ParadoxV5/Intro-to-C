// Caution: Check for EOF and other errors not included in this example.

#include <inttypes.h>
#include <string.h> // for `strchr`

// “Std. IO” library
#include <stdio.h>

#define STRATEGY(title) puts("\n"title);

int main() {
  char string[12]; // 10 + 1 enter key char ('\n') + 1 for the null terminator
  
  #if __STDC_VERSION__ < 201100 // C11 removed `gets`
    STRATEGY("Simple IO")
    // Deprecated: zero protection against array overflow
    gets(string);
    string[10] = '\0'; // Chop `string` off at length 10
    puts(string);
    // `gets` removes the '\n'; `puts` adds a '\n'
  #endif
  
  STRATEGY("Char by char")
  char c = '\0'; // Initialize to something not '\n'
  // Read until '\n'
  for(int_fast8_t i = 0; c != '\n'; ++i) {
    c = (char)getchar(); // returns is signed int to accommodate EOF (which is -1 in some platforms)
    if(i < 10)  // Only store until 10 length
      string[i] = c;
  }
  // Write until '\0'
  char* c_p = string;
  do {
    c = *c_p;
    putchar(c);
    ++c_p;
  } while(c != '\0');
    // Or use for loop with index to stop after 10 length
  putchar('\n');
  // Not `getc`/`putc`!
  
  // Only the above strategies discard the '\n' and any chars before it that exceed length
  #define FLUSH while(getchar() != '\n');
  
  STRATEGY("Specific IO stream")
  fgets(string, 12, stdin); // Recommended alternative to `gets`
  if(!strchr(string, '\n')) // if '\n' not in `string`
    FLUSH // `fgets` does not discard chars that exceed length
  string[10] = '\0'; // `fgets` keeps the '\n'
  fputs(string, stdout);
  fputc('\n', stdout); // also: fgetc(FILE*)
  // also: `stderr`
  
  STRATEGY("Formatted")
  scanf("%10s", string); // Read a max-10-length string
  FLUSH // `scanf` does not take the '\n' nor any chars that exceed length
  printf("%s\n", string); // Or `%-10s` to chop off at 10 length

  STRATEGY("Formatted, Specific IO stream")
  fscanf(stdin, "%10s", string); // Read a max-10-length string
  FLUSH // neither does `fscanf`
  fprintf(stdout, "%-10s\n", string); // ditto
}
