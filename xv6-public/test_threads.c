#include "types.h"
#include "user.h"
#include "x86.h"

#define SLEEP_TIME 50

volatile int shared_counter = 0;
lock_t mutex;

void thread_function(void* arg1, void* arg2) {
  lock_acquire(&mutex);
  shared_counter++;
  printf(1, "Thread %d increased counter to %d\n", *(int*)arg1, shared_counter);
  lock_release(&mutex);
  sleep(SLEEP_TIME);
  exit();
}

int main(int argc, char *argv[]) {
  lock_init(&mutex);
  int thread_id1 = 1, thread_id2 = 2, thread_id3 = 3, arg = 2;

  thread_create(thread_function, (void*)&thread_id1, (void*)arg);
  thread_create(thread_function, (void*)&thread_id2, (void*)arg);
  thread_create(thread_function, (void*)&thread_id3, (void*)arg);

  for (int i = 0; i < 3; i++)
    thread_join();

  printf(1, "Final Counter Value: %d\n", shared_counter);
  exit();
}
