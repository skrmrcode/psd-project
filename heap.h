#define HEAP_H
#include "activity.h"

typedef struct c_heap *heap;

heap newHeap(int size);
void addAct(heap h, activity a);
activity extractMaxPrio(heap h);
void deleteHeap(heap h);
void printHeap(heap h);

int getNumElem(heap h);
activity getActivity(heap h, int index);
