#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "heap.h"
#include "menu.h"

int main(){
    heap h = newHeap(100);
    loadActivities(h);
    int choice;

    while(1){
        showMenu();
        scanf("%d", &choice);
        getchar(); //"delete" the new line
        handleChoice(h, choice);
        }
    }