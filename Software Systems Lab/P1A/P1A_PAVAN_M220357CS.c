// // P1A

// //#1.program

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// int main()
// {
//     int n;
//     int courseCodes[100];
//     printf("Enter the no of courses:");
//     scanf("%d", &n);
//     printf("\nEnter course codes:");
//     for (int i = 0; i < n; i++)
//     {
//         scanf("%d", courseCodes[i]);
//     }
//     for (int i = 0; i < n; i++)
//     {
//         printf("\n%d", courseCodes[i]);
//     }

//     return 0;
// }

// //#2.program

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// int main()
// {

//     char courseCodes[10][10];
//     int n;
//     printf("Enter the no of courses:");
//     scanf("%d", &n);
//     printf("\nEnter course codes:");

//     for (int i = 0; i < n; i++)
//     {
//         scanf("%s", courseCodes[i]);
//     }
//     for (int i = 0; i < n; i++)
//     {
//         printf("\n%s", courseCodes[i]);
//     }
//     return 0;
// }

// //#3.program

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// struct course
// {
//     char code[10];
//     char name[5];
//     int credits;
// };

// struct course courseCodes[10];
// int n;

// void createList()
// {
//     printf("Enter the no of courses:");
//     scanf("%d", &n);
//     for (int i = 0; i < n; i++)
//     {
//         printf("Enter the course details of course %d:", i + 1);
//         scanf("%s", &courseCodes[i].code);
//         scanf("%s", &courseCodes[i].name);
//         scanf("%d", &courseCodes[i].credits);
//     }
//     return;
// }

// int compareStrings(char str1[], char str2[])
// {
//     int i = 0, check = 1; // same strings
//     while (str1[i] != '\0' || str2[i] != '\0')
//     {
//         if (str1[i] != str2[i++])
//         {
//             check = 0; // diff strings
//             break;
//         }
//     }
//     return check;
// }

// int getCredits(struct course courseCodes[], char code[])
// {
//     for (int i = 0; i < n; i++)
//     {
//         // if(strcmp(courseCodes[i].code,code)==0){// strings compare function..
//         if (compareStrings(courseCodes[i].code, code))
//         { // function for comparing
//             return courseCodes[i].credits;
//         }
//     }
//     return '\0';
// }

// int main()
// {
//     char code[10];
//     createList();
//     printf("\nEnter the course code:");
//     scanf("%s", code);
//     if (!getCredits(courseCodes, code))
//     {
//         printf("Course Code Not Found");
//     }
//     else
//     {
//         printf("\nCredits for the course code is: %d", getCredits(courseCodes, code));
//     }

//     return 0;
// }

// //#4.program

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// struct course
// {
//     char code[10];
//     char name[5];
//     int credits;
// };

// void createFile(struct course[], int);

// struct course courseCodes[10];
// int n;
// FILE *fp;

// void createList()
// {
//     printf("Enter the no of courses:");
//     scanf("%d", &n);
//     for (int i = 0; i < n; i++)
//     {
//         printf("Enter the course details of course %d:", i + 1);
//         scanf("%s", &courseCodes[i].code);
//         scanf("%s", &courseCodes[i].name);
//         scanf("%d", &courseCodes[i].credits);
//     }
//     return;
// }

// void createFile(struct course courseCodes[], int noOfCourses)
// {
//     fp = fopen("course.txt", "w");
//     if (!fp)
//     {
//         printf("Error!");
//         exit(1);
//     }
//     for (int i = 0; i < noOfCourses; i++)
//     {
//         fprintf(fp, "%s %s %d\n", courseCodes[i].code, courseCodes[i].name, courseCodes[i].credits);
//     }
//     fclose(fp);
//     return;
// }

// int main()
// {
//     char code[10];
//     createList();
//     createFile(courseCodes, n);
//     return 0;
// }

// // P1A_PAVAN_M220357CS

//#Program(5)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct course
{
    char code[10];
    char name[10];
    int credits;
};

void createList(char[]);
int getCredits(struct course *[], char[]);

FILE *fptr;
int n; // no of courses.

struct course *courseDetails[10];

int main(int argc, char **args)
{
    char code[10];
    int credits;
    createList(args[1]);
    printf("\nEnter the course code to get credits of that course:");
    scanf("%s", code);
    credits = getCredits(courseDetails, code);
    if (!credits)
    {
        printf("\nCourse Not Found!");
    }
    else
    {
        printf("\nCredits for the course %s:%d\n", code, credits);
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
    while (fscanf(fptr, "%s %s %d",
                  courseDetails[i]->code,
                  courseDetails[i]->name,
                  &courseDetails[i]->credits) != EOF)
    {
        courseDetails[++i] = (struct course *)malloc(sizeof(struct course));
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
