#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "activity.h"

struct c_act{
    char description[256];
    char course[100];
    char deadline[11]; //formato yyyy-mm-dd
    int estimatedActTime;
    int timeSpentAct;
    priority p;
    c_state state;
};

activity newAct(char *descr, char* course, char* deadline, int time, priority p){
    activity a = malloc(sizeof(struct c_act));


    strncpy(a->description, descr, 100);
    strncpy(a->course, course, 50);
    strncpy(a->deadline, deadline, 11);

    a->estimatedActTime = time;
    a->timeSpentAct = 0;
    a->p = p;
    a->state = UNCOMPLETED;

    return a;
}

void updateProgress(activity a, int hours){
    a->timeSpentAct += hours;

    if(a->timeSpentAct >= a->estimatedActTime){
        a->state = COMPLETED;
    }
    else{
        a->state = ONGOING;
    }
}

char* getDeadline(activity a){
    return a->deadline;
}

c_state getState(activity a){
    return a->state;
}

priority getP(activity a){
    return a->p;
}

void printAct(activity a){
    char *states[] = {"Uncompleted", "Ongoing", "Completed"};
    char *prio[] = {"", "Low", "Medium", "High"};
    printf("Activity: %s | course: %s | Deadline: %s | priority: %s | State: %s\n", a->description, a->course, a->deadline, states[getState(a)], prio[getP(a)] );
}