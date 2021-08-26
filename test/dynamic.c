#include <stdio.h>

#include <mem_mam.h>

int main (void) {
  int* a = (int*) mm_alloc(sizeof(int), NULL, NULL);
  *a = 3;
  mm_print();
  printf("a = %d\n", *a);
  mm_tracker_node_t* capture_b;
  int* b = (int*) mm_alloc(sizeof(int), NULL, &capture_b);
  *b = 3;
  mm_print();
  printf("b = %d\n", *b);
  printf("Captured node %p\n", capture_b);
  mm_dealloc(capture_b);
  mm_print();
  mm_collect();
  mm_print();
  int* c = (int*) mm_alloc(sizeof(int), NULL, NULL);
  *c = 3;
  mm_print();
  atexit(mm_print);
  atexit(mm_collect);
}
