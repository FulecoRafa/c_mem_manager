#include <stdio.h>
#include <pthread.h>
#include <mem_mam.h>

int thread_count = 0;
int t = 0;

void* subrotine() {
  mm_tracker_node_t* capture;
  int* a = (int*) mm_alloc(sizeof(int), NULL, &capture);
  *a = thread_count++;
  // mm_print();
  // mm_dealloc(capture);
  mm_print();
}

int main(void) {
  mm_init();
  int thread_num = 4;
  atexit(mm_print);
  atexit(mm_stop);
  pthread_t threads[4];
  for (int i = 0; i < thread_num; i++) {
    pthread_create(threads + i, NULL, &subrotine, NULL);
  }
  for (int i = 0; i < thread_num; i++) {
    pthread_join(threads[i], NULL);
  }
  printf("======ENDING PROGRAM======\n");
  return 0;
}
