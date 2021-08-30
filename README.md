# 1. C_MEM_MANAGER `0.2.0`
A simple, thread safe memory manager for C and C++.

# 2. Index
- [1. C_MEM_MANAGER `0.2.0`](#1-c_mem_manager-020)
- [2. Index](#2-index)
- [3. Installation](#3-installation)
- [4. Usage](#4-usage)
- [5. Changelog](#5-changelog)
  - [5.1. 0.2.0](#51-020)
  - [5.2. 0.1.0](#52-010)
# 3. Installation
1. Clone repository in or pc
```bash
git clone https://github.com/FulecoRafa/c_mem_manager.git
```

2. Install library
```bash
sudo make install
```

3. Compile your project with the `-lmem_mam` and `-lpthread` flags. `Pthread` is need
   for thread safety in garbage collector
```bash
gcc my_program.c -lmem_mam -lpthread -o my_program
```

4. Profit!

# 4. Usage
The first step is to start the library:
```cpp
#include <stdio.h>
#include <mem_mam.h>

int main(void) {
  mm_start();
  return 0;
}
```
C_MEM_MANAGER uses functions that 'overload' the usual memory allocation functions.

To allocate memory, use `mm_alloc`

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

The second is a deallocation function.
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
want to clear all the memory allocated until then
```cpp
int main (void) {
  int* my_heap_int = (int*) mm_alloc(sizeof(int), NULL, NULL);
  *my_heap_int = 3;
  mm_collect(); // Manual collection
  int* other_heap_int = (int*) mm_alloc(sizeof(int), NULL, NULL); // This is a memory leak
  *other_heap_int = 3;

  return 0;
}
```

Lastly, to close the library, you need to call `mm_stop`. This clears the library allocations and collects the garbage for you.
You can call it at the end of `main`,
although we recommend you pass it to the `atexit`
stack so that, if your application exits abruptly, it
clears your allocations thread safe and more surely.

```cpp
int main (void) {
  atexit(mm_stop);
  int* my_heap_int = (int*) mm_alloc(sizeof(int), NULL, NULL);
  *my_heap_int = 3;
  int* other_heap_int = (int*) mm_alloc(sizeof(int), NULL, NULL); // This is a memory leak
  *other_heap_int = 3;

  return 0;
}
```

# 5. Changelog
## 5.1. 0.2.0
Added
- Support for multithreading
- Safety in multithreading allocations

Fixed
- Single item deallocation bug

## 5.2. 0.1.0
Added
- Garbage collector (single thead)
