#ifndef HEAP_H
#define HEAP_H

#include "activity.h"

// Abstract data type for a heap of activities
typedef struct c_heap *heap;

// Create a new heap with given capacity
heap newHeap(int size);

// Add a new activity to the heap
void addAct(heap h, activity a);

// Remove and return the activity with the highest priority
activity extractMaxPrio(heap h);

// Free all memory used by the heap and its activities
void deleteHeap(heap h);

// Print all activities in the heap
void printHeap(heap h);

// Return the number of elements in the heap
int getNumElem(heap h);

// Get the activity at a specific index
activity getActivity(heap h, int index);

#endif
