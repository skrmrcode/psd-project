#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <time.h>

// Enumeration representing the state of an activity
typedef enum { UNCOMPLETED, ONGOING, COMPLETED } c_state;

// Enumeration representing the priority level of an activity
typedef enum { NONE = 0, LOW = 1, MEDIUM = 2, HIGH = 3 } priority;

// Abstract data type for an activity
typedef struct c_act* activity;

// Creation and update functions
activity newAct(char *descr, char *course, char *deadline, int time, priority p);
void updateProgress(activity a, int hours);

// Getters for activity attributes
char* getDescr(activity a);
char* getCourse(activity a);
char* getDeadline(activity a);
char* getCreatedDate(activity a);
int getWorkedHours(activity a);
int getTimeReq(activity a);
priority getP(activity a);
c_state getState(activity a);

// Setters
void setCreatedDate(activity a, const char* date);

// Utility functions
void printAct(activity a);
int isLate(activity a);
time_t dataConvert(char* data_str);
char* priorityToStr(int p);

#endif
