#include <stdio.h>

// Function prototype declaration
int write(const char* text); // arg names are optional in signatures
// `typedef` function prototype
typedef int print_func(const char* text); // ditto
// Prototype declaration using `typedef`
print_func write_line;
// Implementations are at the end of this file.

// Use prototype in arg and return types
print_func* function_ception(print_func func) {
  return func; // The arg `func` is actually autocorrected to type `print_func*` – see below
}

int main() {
  #define ASSERT_PRINTS(call) if(call < 0) return 1;
  
  // Functions are usable via their declarations regardless where they are defined.
  ASSERT_PRINTS(write("Hello "))
  ASSERT_PRINTS(write_line("from prototypes!"))
  
  // This is a variable – the type is a pointer to a function
  int (*speak)(const char* message) = &write; // arg names are again optional
  // `typedef` function pointer
  typedef int (*print_func_ptr)(const char* message); // ditto
  /*
     The `&` is optional for function pointers. In fact, C autocorrects between functions and their pointers.
     All of these are valid: `write_line`, `&write_line`, `*write_line`, `**********write_line`
   */
  print_func_ptr say = write_line;
  // Function pointers are usable the same way regular functions are.
  ASSERT_PRINTS((*speak)("Hello again "))
  /*
    Again, the `*` is optional thanks to autocorrects. All of these are valid:
    `say(…)`, `(say)(…)`, `(*say)(…)`, `(**********say)(…)`
    Note that because `say` is a plain o’ variable (whereas `write_line` is a function),
    `&say` fetches its address, so `(&say)(…)` will implode.
    Also beware that `*say(…)` is equivalent to `*(say(…))`  because of the order of operations.
  */
  ASSERT_PRINTS(say("from pointers!"))
  
  // Pass function (pointer) as an arg and use call a returned function pointer – again, autocorrects
  ASSERT_PRINTS(function_ception(write)("Hello once again "))
  ASSERT_PRINTS(function_ception(say)("from `function_ception`!!"))
  
  // Function address analysis – these should be sorted lowest-to-highest
  #define L(label) "\n%p => "#label
  ASSERT_PRINTS(printf(
    L(function_ception) L(main) L(write) L(speak) L(write_line) L(say) "\n",
      function_ception,   main,   write,   speak,   write_line,   say
  ))
}

// Function definitions
int write(const char* text) {
  return fputs(text, stdout);
}
/* Note: must rewrite the signature
  * cannot assign to a function prototype
  * cannot use a `typedef` (function or pointer) to define a function
*/
int write_line(const char* text) {
  return puts(text);
}
