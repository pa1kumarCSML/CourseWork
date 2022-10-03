#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "queue.h"

void maxHeapify(struct courseWaitList *[], int, int);
void heapIncreaseKey(struct courseWaitList *[], int, int);
int LEFT(int i)
{
    return 2 * i;
}
int RIGHT(int i)
{
    return 2 * i + 1;
}
int PARENT(int i)
{
    return i / 2;
}

// Priority Queues using MaxHeap.
void enQueue(char studentname[], struct course *courseData, int key)
{
    struct courseWaitList *temp = (struct courseWaitList *)malloc(sizeof(struct courseWaitList));
    strcpy(temp->studentname, studentname);
    temp->key = INT_MIN;
    courseData->waitListSize += 1;
    courseData->waitList[courseData->waitListSize] = temp;
    heapIncreaseKey(courseData->waitList, courseData->waitListSize, key);
    printf("%s inserted into Priority Queue of %s Succesfully.", studentname, courseData->code);
    return;
}

struct courseWaitList *extract_Max(struct course *courseData)
{
    int n;
    struct courseWaitList **A, *max;
    A = courseData->waitList;
    n = courseData->waitListSize;
    if (n < 1)
    {
        // printf("\nHeap Underflow!!");
        return NULL;
    }
    max = A[1];
    A[1] = A[n];
    n = n - 1;
    courseData->waitListSize--;
    maxHeapify(A, n, 1);
    return max;
}

int isEmptyQueue(struct course *courseData)
{
    return courseData->waitListSize;
}

void heapIncreaseKey(struct courseWaitList *A[], int i, int key)
{
    while (key < A[i]->key)
    {
        printf("\nNew key is smaller than current key!!\nEnter new Key: ");
        scanf("%d", &key);
    }
    A[i]->key = key;
    while (i > 1 && A[PARENT(i)]->key < A[i]->key)
    {
        struct courseWaitList *temp;
        temp = A[i];
        A[i] = A[PARENT(i)];
        A[PARENT(i)] = temp;
        i = PARENT(i);
    }
    return;
}

void maxHeapify(struct courseWaitList *A[], int n, int i)
{
    int left, right, largest;
    left = LEFT(i);
    right = RIGHT(i);
    if (!(left > n) && A[left]->key > A[right]->key)
    {
        largest = left;
    }
    else
    {
        largest = i;
    }
    if (!(right > n) && A[right]->key > A[largest]->key)
    {
        largest = right;
    }
    if (largest != i)
    {
        struct courseWaitList *temp;
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        maxHeapify(A, n, largest);
    }
    return;
}

void increaseKey(char studentname[], char coursename[], struct course *courseDetails[], int n, int key)
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
    if (!courseDetails[i]->waitListSize)
    {
        printf("\nPriority Queue is empty!!");
        return;
    }
    for (int j = 1; j < courseDetails[i]->waitListSize + 1; j++)
    {
        if (!strcmp(studentname, courseDetails[i]->waitList[j]->studentname))
        {
            heapIncreaseKey(courseDetails[i]->waitList, j, key);
            printf("\nKey Increased Successfully.");
            return;
        }
    }
    printf("Student %s not found in the waiting List.", studentname);
    return;
}