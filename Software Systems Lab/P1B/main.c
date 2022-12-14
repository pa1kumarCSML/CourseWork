#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

struct course *courseDetails[10];

void createList(char[]);
int getCredits(struct course *[], char[]);

FILE *fptr;
int n; // no of courses.

int main(int argc, char **args)
{
    char code[10], studentName[20];
    int credits;
    createList(args[1]);
    int choose = 0;
    while (1)
    {
        printf("\n\n1.Insert student\n2.Delete student\n3.Exit");
        printf("\nEnter valid option: ");
        scanf("%d", &choose);
        if (choose == 3)
        {
            break;
        }
        else if (choose != 1 && choose != 2)
        {
            printf("\nInvalid option!!\n");
        }
        else
        {
            printf("\nEnter student name: ");
            scanf("%s", studentName);
            printf("\nEnter Course code: ");
            scanf("%s", code);
            if (choose == 1)
            {
                insert(code, studentName, courseDetails, n);
            }
            else if (choose == 2)
            {
                delete (code, studentName, courseDetails, n);
            }
        }
    }
    return 0;
}

void createList(char filename[])
{
    int i = 0;
    fptr = fopen(filename, "r");
    if (!fptr)
    {
        printf("Error!, File Not Found");
        exit(1);
    }

    courseDetails[i] = (struct course *)malloc(sizeof(struct course));
    courseDetails[i]->regList = NULL;
    courseDetails[i]->waitList = NULL;
    while (fscanf(fptr, "%s %s %d %d",
                  courseDetails[i]->code,
                  courseDetails[i]->name,
                  &courseDetails[i]->credits,
                  &courseDetails[i]->maxLimit) != EOF)
    {
        courseDetails[++i] = (struct course *)malloc(sizeof(struct course));
        courseDetails[i]->regList = NULL;
        courseDetails[i]->waitList = NULL;
    }
    n = i;
    free(courseDetails[i]);
    fclose(fptr);
    return;
}

int getCredits(struct course *courseDetails[], char code[])
{
    for (int i = 0; i < n; i++)
    {
        if (!strcmp(courseDetails[i]->code, code))
            return courseDetails[i]->credits;
    }
    return '\0';
}