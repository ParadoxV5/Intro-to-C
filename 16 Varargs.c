#include <stdio.h>

// `argc`+`argv` style – arrays are poor men’s varargs – except C doesn’t actually has arrays, does it?
void putlines_v(size_t argc, char** argv) {
  // This example could alternatively use a {NULL} pointer to indicate the end of the array similar to Strings,
  // except arrays aren’t typically `null`-terminated but rather are of a known size.
  for(; argc; --argc) // A reminder that `size_t` is unsigned
    puts(*(argv++));
}

// Variadic functions may be called with zero to any number of non-mandatory arguments.
// Variadic args (varargs) can only be after mandatory args, not before.

#include <stdarg.h> // Functions and macros for accessing varargs
// Varargs is how `s`/`printf` functions are implemented.
void putlines(size_t n, ...) {
  va_list args; // Declare the VarArgs object, which holds information to track the vararg traversal.
  va_start(args, n); // Prepare; the `n` informs C the last mandatory arg, after which are the varargs (unused in C23)
  // This example too can use {NULL}-terminate varargs, but until C23, there must be at least one mandatory arg anyways.
  for(; n; --n)
    puts(va_arg(args, char*)); // Query an `arg` from the list given then (expected) type (size)
    // Caution: varargs can only read values of type `int`, `double` or larger.
  /*
    While `va_list`s can be passed to other functions,
    `va_start` and `va_end` must be within the function the `va_list` is for. 
    Also in C99: `va_copy`: Dup the varargs object – important because `va_list`s are single-use only (wherever it is).
  */
  va_end(args); // GC the VarArgs data
}

/*
  Ever heard about the old and obsolete K&R-style functions?
  [According to Jim Fisher](https://jameshfisher.com/2016/11/27/c-k-and-r/),
  It’s actually more than a syntax difference!
  
  The arg list in this style is only part of the implementation (as if they are local vars).
  The compiler will accept any number and type of args because the list is undefined in the declaration.
  This leaves the door to wrong arg errors wide open.
  The real way to define an arg-less function this entire time is actually with `(void)`,
  for compiler in fact treats the “modern” `()` as that garbage K&R style with an empty list for the implementation.
  
  C23 and C++ deleted the restraining K&R style, so their `()` mean `(void)`.
  This also opens the freedom to leave unused args unnamed.
*/
int main(void) {
  char* from = "from";
  // call `argc`+`argv` function with C99 compound literal
  putlines_v(4, (char*[4]){"Hello", from, "array!", ""});
  // call vararg functions just like regular functions
  putlines(3, "Hello again", from, "varargs!!");
}
