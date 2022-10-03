#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

static int regListCount(struct courseRegisterList *regList)
{
    int count = 0;
    while (regList)
    {
        count++;
        regList = regList->nextstudent;
    }
    return count;
}

void insert(char coursename[], char studentname[], struct course *courseDetails[], int n)
{
    int i = 0;
    for (; i < n; i++) // to get the course..
    {
        if (!strcmp(courseDetails[i]->code, coursename))
        {
            break;
        }
    }
    if (i == n)
    {
        printf("\nCourse not found!!");
        return;
    }
    if (!courseDetails[i]->maxLimit)
    {
        printf("\nRegistrations unavailable for the course %s", coursename);
        return;
    }
    if (!(regListCount(courseDetails[i]->regList) <
          courseDetails[i]->maxLimit)) // check maxLimit
    {
        enQueue(studentname, courseDetails[i]); // inserts into waiting list.
        return;
    }

    struct courseRegisterList *temp =
        (struct courseRegisterList *)malloc(sizeof(struct courseRegisterList));
    strcpy(temp->studentname, studentname);
    struct courseRegisterList *cur, *prev;
    cur = prev = courseDetails[i]->regList;
    if (!cur || (strcmp(studentname, cur->studentname) < 0))
    { // if list is empty or insert at beggining.
        temp->nextstudent = cur;
        courseDetails[i]->regList = temp;
    }
    else // if list is not empty.
    {
        while (cur && strcmp(studentname, cur->studentname) > 0) // at middle and at end of the list.
        {
            prev = cur;
            cur = cur->nextstudent;
        }
        temp->nextstudent = cur;
        prev->nextstudent = temp;
    }
    printf("\nStudent %s has registered for the course %s successfully.", studentname, coursename);
    return;
}

void delete (char coursename[], char studentname[], struct course *courseDetails[], int n)
{
    int i = 0, deQueueFlag = 0;
    for (; i < n; i++) // to get the course..
    {
        if (!strcmp(courseDetails[i]->code, coursename))
        {
            break;
        }
    }
    if (i == n)
    {
        printf("\nCourse not found!!");
        return;
    }
    if (!courseDetails[i]->regList)
    {
        printf("\nNo students have registered for the course %s", coursename);
        return;
    }
    struct courseRegisterList *cur;
    struct courseRegisterList *prev;
    cur = prev = courseDetails[i]->regList;
    if (!strcmp(cur->studentname, studentname))
    { // student found at head of reglist.
        courseDetails[i]->regList = cur->nextstudent;
        printf("\nStudent %s unregistered from the course %s successfully.", studentname, coursename);
        free(cur);
        deQueueFlag = deQueue(studentname, courseDetails[i]);
        if (deQueueFlag){
            insert(coursename, studentname, courseDetails, n);
        }
        return;
    }
    cur = cur->nextstudent;
    while (cur) // student found at middle or end.
    {
        if (!strcmp(cur->studentname, studentname))
        {
            prev->nextstudent = cur->nextstudent;
            free(cur);
            printf("\nStudent %s unregistered from the course %s successfully.", studentname, coursename);
            deQueueFlag = deQueue(studentname, courseDetails[i]);
            if (deQueueFlag){

                insert(coursename, studentname, courseDetails, n);
            }
            return;
        }
        prev = cur;
        cur = cur->nextstudent;
    }

    printf("\n%s has not registered for the course %s", studentname, coursename);
    return;
}