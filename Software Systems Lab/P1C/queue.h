
struct courseRegisterList // BST
{
    char studentname[10];
    struct courseRegisterList *left;
    struct courseRegisterList *right;
    struct courseRegisterList *parent;
};
struct courseWaitList // Priority Queue using MaxHeap
{
    char studentname[20];
    int key;
};
struct course
{
    char code[10];
    char name[10];
    int credits;
    int maxLimit;
    struct courseRegisterList *regList;
    struct courseWaitList *waitList[20];
    int waitListSize;
};

void enQueue(char[], struct course *, int);
struct courseWaitList *extract_Max(struct course *);
int isEmptyQueue(struct course *);
void increaseKey(char[], char[], struct course *[], int, int);