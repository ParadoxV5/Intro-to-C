
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
}
