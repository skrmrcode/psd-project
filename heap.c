#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

struct c_heap{
    activity *arr;
    int numElem;
    int capacity;
};

void swap(activity *a, activity *b){
    activity temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(heap h, int pos){
    while(pos > 0){
        int parent = (pos - 1) / 2;
        if(getP(h->arr[pos]) > getP(h->arr[parent])){
            swap(&h->arr[pos], &h->arr[parent]);
            pos = parent;
        }
        else{
            break;
        }
    }
}

void heapifyDown(heap h, int pos){
    int max = pos;
    int sx = 2 * pos;
    int dx = 2 * pos + 1;

    if (sx < h->numElem && getP(h->arr[sx]) > getP(h->arr[max]))
        max = sx;
    if (dx < h->numElem && getP(h->arr[dx]) > getP(h->arr[max]))
        max = dx;

    if (max != pos) {
        swap(&h->arr[pos], &h->arr[max]);
        scendi(h, max);
    }
}

heap newHeap(int size){
    heap h = malloc(sizeof(struct c_heap));
    h->numElem = 0;
    h->capacity = size;
    h->arr = malloc(sizeof(activity) * size);
    return h;
}

void addAct(heap h, activity a){
    if(h->numElem >= h->capacity){
        printf(("FULL"));
        return;
    }
    else{
        h->arr[h->numElem] = a;
        heapifyUp(h, h->numElem);
        h->numElem++;
    }
}

activity extractMaxPrio(heap h) {
    if (h->numElem == 0) return NULL;

    activity top = h->arr[0];
    h->arr[0] = h->arr[h->numElem--];
    heapifyDown(h, 0);
    return top;
}

void deleteHeap(heap h) {
    for (int i = 0; i < h->numElem; i++) {
        free(h->arr[i]);
    }
    free(h->arr);
    free(h);
}

void printHeap(heap h) {
    for (int i = 0; i < h->numElem; i++) {
        printAct(h->arr[i]);
    }
}

int getNumElem(heap h) {
    return h->numElem;
}

activity getActivity(heap h, int index) {
    if (index >= 0 && index < h->numElem) {
        return h->arr[index];
    }
    return NULL;
}


time_t convertDate(char* data_str) {
    int y, m, d;
    sscanf(data_str, "%d-%d-%d", &y, &m, &d);

    struct tm tm = {0};
    tm.tm_year = y - 1900;
    tm.tm_mon = m - 1;
    tm.tm_mday = d;

    return mktime(&tm);
}


int IsLate(activity a) {
    if (getState(a) == COMPLETED)
        return 0;

    time_t deadline = convertDate(getDeadline(a));
    time_t today = time(NULL);

    return difftime(today, deadline) > 0;
}
