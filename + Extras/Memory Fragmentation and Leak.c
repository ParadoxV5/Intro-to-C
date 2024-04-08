#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

const size_t MALLOC_SIZE = sizeof(void*) * 3; // Est. minimum `malloc` size

int main() {
  size_t count, kibibytes;
  void* ptr;
  puts("Open Task Manager, `top` or etc. to monitor this program’s memory usage.\n");
  
  printf("Enter the number of bytes to allocate: ");
  scanf("%zu", &count);
  getchar(); // Eat the Enter keypress
  kibibytes = count / 1024;
  
  printf("Claiming %zu KiB...\n", kibibytes);
  ptr = malloc(count);
  printf("%zu KiB claimed. Press Enter to continue - ", kibibytes);
  getchar();
  
  printf("Releasing %zu KiB...\n", kibibytes);
  free(ptr);
  
  count /= MALLOC_SIZE;
  printf("Claiming %zu bytes %zu times...\n", MALLOC_SIZE, count);
  for(size_t c = 0; c < count; ++c)
    ptr = malloc(MALLOC_SIZE);
  printf("%zu bytes claimed %zu times. Press Enter to continue - ", MALLOC_SIZE, count);
  getchar();
  
  printf("Relying on the OS to free %zu bytes %zu times...\n", MALLOC_SIZE, count);
    // since a bunch of them are simply unreachable
}
