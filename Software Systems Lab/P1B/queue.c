#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

void enQueue(char studentname[], struct course *courseData)
{
    struct courseWaitList *temp = (struct courseWaitList *)malloc(sizeof(struct courseWaitList));
    strcpy(temp->studentname, studentname);
    temp->prevstudent = NULL;
    temp->nextstudent = NULL;
    struct courseWaitList *cur = isEmptyQueue(courseData);
    if (!cur) // emptyQueue;
    {
        courseData->waitList = temp;
    }
    else
    {
        while (cur->nextstudent)
        {
            cur = cur->nextstudent;
        }
        cur->nextstudent = temp;
        temp->prevstudent = cur;
    }
    printf("\nStudent %s enqeued into waiting list of course %s", studentname, courseData->code);
    return;
}

int deQueue(char *studentname, struct course *courseData)
{
    struct courseWaitList *cur = isEmptyQueue(courseData);
    if (!cur)
    { // emptyqueue
        // printf("\nQueue is empty!!");
        return 0;
    }
    strcpy(studentname, cur->studentname);

    if (!cur->nextstudent)
    { // when only one node in dll.
        courseData->waitList = cur->nextstudent;
    }
    else
    { // when more than nodes in dll.
        courseData->waitList = cur->nextstudent;
        cur->nextstudent->prevstudent = NULL;
    }
    free(cur);
    return 1;
}

struct courseWaitList *isEmptyQueue(struct course *courseData)
{
    return courseData->waitList;
}