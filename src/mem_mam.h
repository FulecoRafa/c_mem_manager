#ifndef MEM_MAN
#define MEM_MAN

#include <stdlib.h>

typedef struct _mm_tracker_node_t mm_tracker_node_t;
typedef struct _mm_tracker_t mm_tracker_t;

void mm_init();
void mm_stop();

/**
 * @brief Allocates space of size `s` while keeping track that it
 *  exists for later clearing. To clear the space, it needs
 *  a deallocation function that receives a void pointer and
 *  frees it. It is possible to track the allocated node
 *  passing a pointer to `capture_node`
 *
 * @param s size allocated
 * @param dealloc_func deallocation function (default: free)
 * @param capture_node node kept track of
 * @return void* pointer to allocated space
 */
void* mm_alloc(size_t s, void (*dealloc_func)(void*), mm_tracker_node_t** capture_node);

/**
 * @brief Takes a reference to a node kept track of
 *  and deallocates it keeping the tracking fine
 *
 * @param node node to dealocate
 */
void mm_dealloc(mm_tracker_node_t* node);

/**
 * @brief Clears all memory kept track of.
 *  As recomendation, pass it to the `atexit` function so
 *  it clear all data as soon as the program ends
 */
void mm_collect(void);

/**
 * @brief Prints tracker
 *
 */
void mm_print(void);

#endif // MEM_MAN
