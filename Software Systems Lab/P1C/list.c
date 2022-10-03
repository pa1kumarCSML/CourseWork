#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

void Transplant(struct course *, struct courseRegisterList *,
                struct courseRegisterList *);
struct courseRegisterList *treeSearch(struct courseRegisterList *, char[]);

struct courseRegisterList *treeMin(struct courseRegisterList *);

int regListCount(struct courseRegisterList *root, int count)
{
    if (root)
    {
        count = regListCount(root->left, count);
        ++count;
        count = regListCount(root->right, count);
    }
    return count;
}

void insert(char coursename[], char studentname[], struct course *courseDetails[], int n)
{
    int i = 0, key = 0;
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
    if (!(regListCount(courseDetails[i]->regList, 0) <
          courseDetails[i]->maxLimit)) // check maxLimit
    {
        printf("\n%s has reached MaxLimit,Student %s is inserting into Priority Queue.", coursename, studentname);
        printf("\nEnter the Priority key: ");
        scanf("%d", &key);
        enQueue(studentname, courseDetails[i], key); // inserts into waiting list(using priorityQueue).
        return;
    }

    struct courseRegisterList *temp, *cur, *parentnode;
    temp = (struct courseRegisterList *)malloc(sizeof(struct courseRegisterList));
    strcpy(temp->studentname, studentname);
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;

    // logic for inserting into BST.

    parentnode = NULL;
    cur = courseDetails[i]->regList; // assigned root
    while (cur)
    {
        parentnode = cur;
        if (strcmp(temp->studentname, cur->studentname) > 0)
        {
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }
    }
    temp->parent = parentnode;
    if (!parentnode)
    {
        courseDetails[i]->regList = temp;
    }
    else if (strcmp(temp->studentname, parentnode->studentname) > 0)
    {
        parentnode->right = temp;
    }
    else
    {
        parentnode->left = temp;
    }
    // inserted..

    printf("\nStudent %s has registered for the course %s successfully.", studentname, coursename);
    return;
}

void delete (char coursename[], char studentname[], struct course *courseDetails[], int n)
{
    int i = 0;
    struct courseWaitList *deQueueFlag = NULL;
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

    struct courseRegisterList *deletenode, *root, *successornode;
    root = courseDetails[i]->regList;
    deletenode = treeSearch(root, studentname);
    if (!deletenode)
    {
        printf("\n%s has not registered for the course %s", studentname, coursename);
        return;
    }

    // logic for deletion of node in BST.
    if (!deletenode->left)
    {

        Transplant(courseDetails[i], deletenode, deletenode->right);
    }
    else if (!deletenode->right)
    {

        Transplant(courseDetails[i], deletenode, deletenode->left);
    }
    else
    {
        successornode = treeMin(deletenode->right);
        if (successornode->parent != deletenode)
        {
            Transplant(courseDetails[i], successornode, successornode->right);
            successornode->right = deletenode->right;
            successornode->right->parent = successornode;
        }
        Transplant(courseDetails[i], deletenode, successornode);
        successornode->left = deletenode->left;
        successornode->left->parent = successornode;
    }

    printf("\nStudent %s deleted from the course %s successfully.", studentname, coursename);

    // logic: after dequeue need to do insert operation..

    deQueueFlag = extract_Max(courseDetails[i]);
    if (deQueueFlag)
    {
        printf("\nStudent %s extracted from the course %s Queue.", deQueueFlag->studentname, coursename);
        insert(coursename, deQueueFlag->studentname, courseDetails, n);
    }
    return;
}

void inorderTreeWalk(struct courseRegisterList *root)
{
    if (root)
    {
        inorderTreeWalk(root->left);
        printf("%s ", root->studentname);
        inorderTreeWalk(root->right);
    }
}

void printRegList(char coursename[], struct course *courseDetails[], int n)
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
    if (!courseDetails[i]->regList)
    {
        printf("\nNo students have registered for the course %s", coursename);
        return;
    }
    else
    { // inorder traversal of the reglist bst.
        int option;
        printf("\n1.With Recursion\n2.With Stack\nEnter option: ");
        scanf("%d", &option);
        if (option == 1)
            inorderTreeWalk(courseDetails[i]->regList);
        else
            inorderTreeWalkWithStack(courseDetails[i]->regList);
    }
    return;
}

void Transplant(struct course *courseData, struct courseRegisterList *u,
                struct courseRegisterList *v)
{
    if (!u->parent)
    {
        courseData->regList = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    if (v)
        v->parent = u->parent;
    free(u);
    return;
}

struct courseRegisterList *treeSearch(struct courseRegisterList *root, char studentname[])
{
    while (root && strcmp(studentname, root->studentname)) // strcmp(temp->studentname, cur->studentname) > 0
    {
        if (strcmp(studentname, root->studentname) > 0)
        {
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }
    return root;
}

struct courseRegisterList *treeMin(struct courseRegisterList *root)
{
    while (root->left)
    {
        root = root->left;
    }
    return root;
}

void push(struct courseRegisterList *stack[], struct courseRegisterList *node, int *top)
{
    stack[++(*top)] = node;
    return;
}

struct courseRegisterList *pop(struct courseRegisterList *stack[], int *top)
{
    struct courseRegisterList *newcur;
    printf("%s ", stack[(*top)]->studentname);
    newcur = stack[(*top)];
    --(*top);
    return newcur;
}

int isEmpty(int top)
{ // 0-Empty otherwise-nonEmpty.
    return top == 0 ? 0 : 1;
}

void inorderTreeWalkWithStack(struct courseRegisterList *root)
{
    struct courseRegisterList *stack[20];
    int top = 0;
    struct courseRegisterList *cur = root;
    int complete = 0;

    while (!complete)
    {
        if (cur)
        {
            push(stack, cur, &top);
            cur = cur->left;
        }
        else
        {
            if (isEmpty(top))
            {
                cur = pop(stack, &top);
                cur = cur->right;
            }
            else
            {
                complete = 1;
            }
        }
    }
    return;
}