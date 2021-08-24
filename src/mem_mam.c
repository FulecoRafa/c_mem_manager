#include "mem_mam.h"
#include <stdlib.h>

struct _mm_tracker_node_t {
  void* val;
  mm_tracker_node_t* left, * right;
  void (*dealloc_func)(void*);
};

typedef struct {
  mm_tracker_node_t* head, * tail;
} mm_tracker_t;

mm_tracker_t MM_Tracker;

mm_tracker_node_t* add_node(void* allocated_data, void* dealloc_func) {
  mm_tracker_node_t *new_node =
    (mm_tracker_node_t*) malloc(sizeof (mm_tracker_node_t));
  new_node->val = allocated_data;
  new_node->dealloc_func = dealloc_func == NULL ? dealloc_func : free;
  if (MM_Tracker.tail == NULL) {
    MM_Tracker.head = MM_Tracker.tail = new_node;
    new_node->left = new_node->right = NULL;
  } else {
    MM_Tracker.tail->right = new_node;
    new_node->left = MM_Tracker.tail;
    MM_Tracker.tail = new_node;
  }

  return new_node;
}

void mm_dealloc(mm_tracker_node_t* node) {
  mm_tracker_node_t* left, * right;
  left = node->left;
  right = node->right;
  node->dealloc_func(node->val);
  node->left = node->right = NULL;
  free(node);
  left->right = right;
  right->left = left;
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
}

void* mm_alloc(size_t s, void (*dealloc_func)(void*), mm_tracker_node_t *capture_node) {
  void* allocated_data = malloc(s);
  mm_tracker_node_t* node = add_node(allocated_data, dealloc_func);
  if (capture_node != NULL)
    capture_node = node;
  return allocated_data;
}
