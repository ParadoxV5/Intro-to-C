#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// Global Scope
static char  gc = 0x0;
static short gs = 0x1;
static int   gi = 0x2;
static long  gl = 0x3;

// File Scope
char  fc = 0x4;
short fs = 0x5;
int   fi = 0x6;
long  fl = 0x7;

int main() {
  // Function Local Scope
  char  lc = 0x8;
  short ls = 0x9;
  int   li = 0xA;
  long  ll = 0xB;
  
  // Heap: Dynamically Allocated (pointers)
  char * pc = malloc(sizeof(char ));
  short* ps = malloc(sizeof(short));
  int  * pi = malloc(sizeof(int  ));
  long * pl = malloc(sizeof(long ));
  
  // TSV
  puts("POINTERS\t`sizeof`\tGlobal\tFile\tLocal\tHeap");
  printf("char \t%zu\t%p\t%p\t%p\t%p\n", sizeof(char ), &gc, &fc, &lc, pc);
  printf("short\t%zu\t%p\t%p\t%p\t%p\n", sizeof(short), &gs, &fs, &ls, ps);
  printf("int  \t%zu\t%p\t%p\t%p\t%p\n", sizeof(int  ), &gi, &fi, &li, pi);
  printf("long \t%zu\t%p\t%p\t%p\t%p\n", sizeof(long ), &gl, &fl, &ll, pl);
  
  // Free the Heap
  free(pc);
  free(ps);
  free(pi);
  free(pl);
}
