# C_MEM_MANAGER
A simple memory manager for C

## Instalation
1. Clone repository in or pc
```bash
git clone https://github.com/FulecoRafa/c_mem_manager.git
```

2. Install library
```bash
sudo make install
```

3. Compile your project with the `-lmem_mam` flag
```bash
gcc my_program.c -lmem_mam -o my_program
```

4. Profit!

## Usage
C_MEM_MANAGER uses functions that 'overload' the usual memory alocation functions.

To alocate memory, use `mm_alloc`

Ex:
```cpp
#include <stdio.h>
#include "mem_mam.h"

int main (void) {
  int* my_heap_int = (int*) mm_alloc(sizeof(int), NULL, NULL);
  *my_heap_int = 3;

  return 0;
}
```

Different from `malloc`, `mm_alloc` receives 3 arguments.

The first is the size, which is equal to what
you would normally pass to `malloc`.

The second is a dealocation function.
This is a pointer to a function that
receives a `void*` as argument and frees the memory.
Use this if you're allocating a custom data type.
If you're using base C pointers to allocate, you can
pass `NULL` and it wil default to `free` function.

The third is a capturer pointer. Use only if you need
to specifically free that pointer manually using the
`mm_dealloc` function:
```cpp
int main (void) {
  mm_tracker_node_t* capture;
  int* my_heap_int = (int*) mm_alloc(sizeof(int), NULL, &capture);
  *my_heap_int = 3;
  mm_dealloc(capture);

  return 0;
}
```

Finally, there is the `mm_collect` function can be used
to 'collect the garbage'. You can call it at anytime you
want, although we recommend you pass it to the `atexit`
stack. This solution works if your application exits
not normally and clears your allocations thread safe.
```cpp
int main (void) {
  atexit(mm_collect); // collect at aplication exit
  int* my_heap_int = (int*) mm_alloc(sizeof(int), NULL, NULL);
  *my_heap_int = 3;
  mm_collect(); // Manual collection
  int* other_heap_int = (int*) mm_alloc(sizeof(int), NULL, NULL);
  *other_heap_int = 3;

  return 0;
}
```
