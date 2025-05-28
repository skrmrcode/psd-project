#ifndef ACTIVITY_H
#define ACTIVITY_H
#include <time.h>
typedef struct c_act *activity;

typedef enum{
    HIGH,
    MEDIUM,
    LOW
} priority;

typedef enum{
    UNCOMPLETED,
    ONGOING,
    COMPLETED
} c_state;

activity newAct();

void updateProgress(activity a, int hours);

void printAct(activity a);

c_state getState(activity a);

priority getP(activity a);

char* getDescr(activity a);
char* getCourse(activity a);
int getWorkedHours(activity a);

int isLate(activity a);

char* getDeadline(activity a);
time_t dataConvert(char* data_str);
#endif