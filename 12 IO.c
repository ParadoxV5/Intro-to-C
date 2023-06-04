// “Std. IO” library
#include <stdio.h>

// Caution: ones that specify a length does not discard chars that exceed length

int main() {
  char string[12]; // 10 + 1 enter key char ('\n') + 1 for the null terminator
  
  #if __STDC_VERSION__ < 201100 // C11 removed `gets`
    // Simple IO //
    // Deprecated: zero protection against array overflow
    gets(string);
    string[10] = '\0';
    puts(string);
    // `gets` removes the '\n'; `puts` adds a '\n'
    putchar('\n'); // also: getchar(); not `putc`/`getc`
  #endif
  
  // Formatted //
  scanf("%10s", string); // Read a max-10-length string
  printf("%-10s\n", string);
  #if __STDC_VERSION__ >= 201100 // New in C11
    scanf_s("%s", string, 10); // `scanf_s` take two args for `%s`
    printf_s("%s\n", string); // with error detection not covered here
  #endif
  // `scanf` and `scanf_s` keep the '\n'
  
  // Specific IO stream //
  // also: `stderr`
  fgets(string, 12, stdin); // Recommended alternative to `gets`
  fputs(string, stdout);
  // `fgets` keeps the '\n'
  fputc('\n', stdout); // also: fgetc(FILE*)
  
  // Formatted, Specific IO stream //
  fscanf(stdin, "%10s", string); // Read a max-10-length string
  fprintf(stdout, "%-10s\n", string);
  #if __STDC_VERSION__ >= 201100 // New in C11
    fscanf_s(stdin, "%s", string, 10); // `fscanf_s` is like `scanf_s`
    fprintf_s(stdout, "%s\n", string); // with error detection not covered here
  #endif
  // `fscanf` and `fscanf` keep the '\n'
}
