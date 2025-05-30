#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

// Structure representing a max-heap of activities
struct c_heap {
    activity *arr;   // Array of activity pointers
    int numElem;     // Current number of elements in the heap
    int capacity;    // Maximum capacity of the heap
};

// Swap two activity pointers
void swap(activity *a, activity *b) {
    activity temp = *a;
    *a = *b;
    *b = temp;
}

// Restore heap property by moving the element at 'pos' up
void heapifyUp(heap h, int pos) {
    while (pos > 0) {
        int parent = (pos - 1) / 2;
        if (getP(h->arr[pos]) > getP(h->arr[parent])) {
            swap(&h->arr[pos], &h->arr[parent]);
            pos = parent;
        } else {
            break;
        }
    }
}

// Restore heap property by moving the element at 'pos' down
void heapifyDown(heap h, int pos) {
    int max = pos;
    int sx = 2 * pos;
    int dx = 2 * pos + 1;

    if (sx < h->numElem && getP(h->arr[sx]) > getP(h->arr[max]))
        max = sx;
    if (dx < h->numElem && getP(h->arr[dx]) > getP(h->arr[max]))
        max = dx;

    if (max != pos) {
        swap(&h->arr[pos], &h->arr[max]);
        heapifyDown(h, max);
    }
}

// Create a new heap with a given size
heap newHeap(int size) {
    heap h = malloc(sizeof(struct c_heap));
    h->numElem = 0;
    h->capacity = size;
    h->arr = malloc(sizeof(activity) * size);
    return h;
}

// Add a new activity to the heap
void addAct(heap h, activity a) {
    if (h->numElem >= h->capacity) {
        printf(("FULL"));
        return;
    } else {
        h->arr[h->numElem] = a;
        heapifyUp(h, h->numElem);
        h->numElem++;
    }
}

// Extract the activity with the highest priority (top of the heap)
activity extractMaxPrio(heap h) {
    if (h->numElem == 0) return NULL;

    activity top = h->arr[0];
    h->arr[0] = h->arr[h->numElem--];
    heapifyDown(h, 0);
    return top;
}

// Free memory associated with the heap and all activities
void deleteHeap(heap h) {
    for (int i = 0; i < h->numElem; i++) {
        free(h->arr[i]);
    }
    free(h->arr);
    free(h);
}

// Print all activities in the heap
void printHeap(heap h) {
    for (int i = 0; i < h->numElem; i++) {
        printAct(h->arr[i]);
    }
}

// Get the current number of elements in the heap
int getNumElem(heap h) {
    return h->numElem;
}

// Get the activity at a specific index
activity getActivity(heap h, int index) {
    if (index >= 0 && index < h->numElem) {
        return h->arr[index];
    }
    return NULL;
}
