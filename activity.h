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

int isLate(activity a);

char* getDeadline(activity a);