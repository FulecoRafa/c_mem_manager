#include "mem_mam.h"
#include <stdlib.h>
#include <stdio.h>

struct _mm_tracker_node_t {
  void* val;
  mm_tracker_node_t* left, * right;
  void (*dealloc_func)(void*);
};

struct _mm_tracker_t {
  mm_tracker_node_t* head, * tail;
};

mm_tracker_t MM_Tracker;

mm_tracker_node_t* add_node(void* allocated_data, void* dealloc_func) {
  mm_tracker_node_t *new_node =
    (mm_tracker_node_t*) malloc(sizeof (mm_tracker_node_t));
  new_node->val = allocated_data;
  new_node->dealloc_func = dealloc_func != NULL ? dealloc_func : free;
  if (MM_Tracker.tail == NULL) {
    MM_Tracker.head = MM_Tracker.tail = new_node;
    new_node->left = new_node->right = NULL;
  } else {
    MM_Tracker.tail->right = new_node;
    new_node->left = MM_Tracker.tail;
    new_node->right = NULL;
    MM_Tracker.tail = new_node;
  }


  return new_node;
}

void mm_dealloc(mm_tracker_node_t* node) {
  if (node == MM_Tracker.head) {
    printf("Is head\n");
    MM_Tracker.head = node->right;
    MM_Tracker.head->left = NULL;
  } else if (node == MM_Tracker.tail) {
    printf("Is tail\n");
    MM_Tracker.tail = node->left;
    MM_Tracker.tail->right = NULL;
  } else {
    mm_tracker_node_t* left, * right;
    left = node->left;
    right = node->right;
    left->right = right;
    right->left = left;
  }
  node->dealloc_func(node->val);
  node->left = node->right = NULL;
  free(node);
}

void mm_collect(void){
  mm_tracker_node_t* this, * next;
  this = MM_Tracker.head;
  while (this != NULL) {
    next = this->right;
    this->dealloc_func(this->val);
    this->left = this->right = NULL;
    free(this);
    this = next;
  }
  MM_Tracker.head = MM_Tracker.tail = NULL;
}

void print_node(mm_tracker_node_t* node) {
  printf("%p", node->val);
}

void mm_print(void) {
  mm_tracker_node_t* this, * next;
  this = MM_Tracker.head;
  while (this != NULL) {
    next = this->right;
    print_node(this);
    printf("->");
    this = next;
  }
  printf("*\n");
}

void* mm_alloc(size_t s, void (*dealloc_func)(void*), mm_tracker_node_t** capture_node) {
  void* allocated_data = malloc(s);
  mm_tracker_node_t* node = add_node(allocated_data, dealloc_func);
  // if (capture_node != NULL)
  printf("Created node %p\n", node);
  if(capture_node)
    *capture_node = node;
  return allocated_data;
}
