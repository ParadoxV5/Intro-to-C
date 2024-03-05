#include <inttypes.h>
#include <stdio.h>
//#undef WIN32
#ifdef WIN32
  #include <windows.h>
#else
  #include <pthread.h>
#endif
#include <unistd.h> // Header for `sleep()` 

int main();

static int assert(int(* actual)()) {
  printf("*thread:\t%p\n*expect:\t%p\n", actual, &main);
  return actual != &main;
}

static
#ifdef WIN32
  DWORD
#else
  void*
#endif
thread_function(void* arg) {
  sleep(2);
  puts("hello, world");
  return
  #ifdef WIN32
    assert
  #endif
    (arg);
}

int main() {
  int error;
  #define LOG(label, blk...) \
    puts("+"#label);\
    blk\
    if(error) {\
      puts("!"#label);\
      return error;\
    }\
    puts("-"#label);
  
  #ifdef WIN32
    DWORD thread_id;
    LOG(CreateThread,
      HANDLE thread_handle = CreateThread(NULL, 0, thread_function, &main, 0, &thread_id);
      error = !thread_handle;
    )
  #else
    pthread_t thread_id;
    LOG(pthread_create,
      error = pthread_create(&thread_id, NULL, thread_function, &main);
    )
  #endif
  printf("thread_id:\t%"PRIxMAX"\n", (intmax_t)thread_id);
  #ifdef WIN32
    LOG(WaitForSingleObject,
      error = (int)WaitForSingleObject(thread_handle, INFINITE);
    )
    LOG(CloseHandle,
      error = !CloseHandle(thread_handle);
    )
  #else
    void* thread_return;
    LOG(pthread_join,
      error = pthread_join(thread_id, &thread_return);
    )
    error = assert(thread_return);
  #endif
  return error;
}
