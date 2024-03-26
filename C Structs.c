#include <limits.h> // for `ULONG_MAX`
#include <string.h> // for `strcpy`
#include <stdio.h>
/*
  A `struct`ure packages multiple variables (called members, just like OOP classes)
  into one data structure, similar to a JSON object.
  Unlike an array, one can compose a struct with a variety of data types.
*/

// define a struct type
struct Msg {
  // Members are listed just like varaibles – you can even use commas if you’re feeling spicy
  short id; // a `short` member
  char info[16]; // a `char[]` member, utilizing the struct’s packaged memory
  void* ref; // a `void*` member, may point anywhere
};
// define a `typedef` for a struct type
typedef struct Msg Msg; // This is automaticlaly done in C++ (including Arduino).
// define a struct type and a `typedef` for it in one go
typedef struct LinkedList {
  void* data;
  struct LinkedList* next; // pointer to struct
} LinkedList;

// a pass-by-value function
int show(struct Msg message) {
  // Read a struct’s members as another function’s arguments
  return printf("[%hi]\t%s\t(%p)\n", message.id, message.info, message.ref);
}
/* a pass-by-reference function
  Structs are typically passed by just a pointer rather than their entire data
  (kinda like arrays in some sense)
*/
void p_list(struct LinkedList* list_p) {
  while(list_p) {
    printf(" %p", list_p->data); // `list_p->data` is syntax sugar for `(*list_p).data`
    list_p = list_p->next;
  }
}

int main() {
  
  // define a struct variable without giving it data
  struct Msg msg1;
  // write a struct’s members
  msg1.id = 1;
  strcpy(msg1.info, "Message Alpha"); // Recall that one does not simply assign one array into another
  //msg1.ref = NULL; // C does not mandate compilers to zero the struct variable when it’s simply declared.
  // pass by value
  show(msg1);
  
  // define a struct variable and assign values array-style
  struct Msg msg2 = {
    -2, // position is inferred from the struct definition
    "message beta" // automatic `strcpy` with literal
    // unset members are automatically zeroed
  };
  show(msg2);
  
  // Designated Initialization (new in C99, not available in C++) is order-agnostic.
  struct Msg msg0 = {
    .ref = &main, // initialize from expression result
    .info = "msg ", // initialize from automatic `strcpy`
    // unset members are again automatically zeroed
  };
  show(msg0);
  
  // copy-by-value a struct
  msg1 = msg0;
  show(msg1);
  //printf("%i", msg0 == msg1); // Can’t compare structs like this
  /* pass-by-value two struct in-line,
    one with the struct type with Designated Initialization,
    one with its `typedef` using array-style
  */
  show((struct Msg){.ref = &show, .info = "&show"});
  show((Msg){-1, "&p_list", &p_list});
  
  // define a struct variable using its `typedef` and assign with Designated Initialization
  LinkedList list = {
    .data = &msg0,
    .next = &(LinkedList){ // ditto, but an in-line reference (`&`)
      .data = &msg1,
      .next = &(struct LinkedList){ // ditto, but with the other set of styles
        &msg2
      }
    }
  };
  // pass-by-reference
  p_list(&list);
  
  /* a struct variable with an unnamed struct type
    Unnamed struct type are inaccessible through `struct …`.
    It can only infer from either the variable or `typedef`.
    Assigning to variables (or args) still requrie the members match exactly.
  */
  struct {
    unsigned short a;
    unsigned long padding;
    unsigned short z;
  } test = {0x1234, ULONG_MAX, 0xABCD}; // Both styles also apply.
  printf("\n%hX %hX\t", test.a, test.z);
  // C also doesn’t mandate structs to pack their bytes tightly.
  short* faux_array = (short*)&test;
  size_t size = sizeof(test) / sizeof(short);
  // Additionally prints things other than `1234`, `ABCD` or `F`s for number or struct paddings
  while(size)
    printf(" %hX", faux_array[--size]);
  putchar('\n');
  
}
