#ifndef QUEUE_H_
#define QUEUE_H_
struct courseRegisterList
{
    char studentname[10];
    struct courseRegisterList *nextstudent;
};
struct courseWaitList
{
    char studentname[10];
    struct courseWaitList *prevstudent;
    struct courseWaitList *nextstudent;
};
struct course
{
    char code[10];
    char name[10];
    int credits;
    int maxLimit;
    struct courseRegisterList *regList;
    struct courseWaitList *waitList;
};
void enQueue(char studentname[], struct course *courseData);
int deQueue(char *studentname, struct course *courseData);
struct courseWaitList *isEmptyQueue(struct course *courseData);

#endif