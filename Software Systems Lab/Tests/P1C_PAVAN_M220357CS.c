#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

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
    char type[10];
    struct courseRegisterList *regList;
    struct courseWaitList *waitList[20];
    int waitListSize;
    int priority;
};
struct course *courseDetails[10];
int n;//noofcourses

void heapIncreaseKey(struct courseWaitList *A[], int i, int key);
void maxHeapify(struct courseWaitList *[], int, int);
void inorderTreeWalk(struct courseRegisterList *root);
struct courseRegisterList *treeMin(struct courseRegisterList *root);
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


void insert(char coursename[], char studentname[], struct course *courseDetails[], int n);
void delete (char coursename[], char studentname[], struct course *courseDetails[], int n);
void getMaxRegisteredCourse(struct course *Courses[],int n);
int regListCount(struct courseRegisterList *root, int count);
void Transplant(struct course *courseData, struct courseRegisterList *u, struct courseRegisterList *v);
struct courseRegisterList *treeSearch(struct courseRegisterList *root, char studentname[]);
void printRegList(char coursename[], struct course *courseDetails[], int n);


void enQueue(char[], struct course *, int);
struct courseWaitList *extract_Max(struct course *);
int isEmptyQueue(struct course *);
void increaseKey(char[], char[], struct course *[], int, int);


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

int main(){
	char character[1];
	char studentName[20],code[20];
	printf("\nEnter No of courses: ");
	scanf("%d",&n);

	for(int i=0;i<n;i++){
	        courseDetails[i] = (struct course *)malloc(sizeof(struct course));
	        scanf("%s %s %s",courseDetails[i]->code,courseDetails[i]->name,
	        courseDetails[i]->type);
	        scanf("%d",&courseDetails[i]->credits);
	        courseDetails[i]->regList=NULL;
	        courseDetails[i]->waitListSize=0;
	        if(!strcmp(courseDetails[i]->type,"Core")){
	          courseDetails[i]->maxLimit=50;
	        }else{//elective
	                courseDetails[i]->maxLimit=3;
	        }
	        courseDetails[i]->priority=courseDetails[i]->maxLimit;
	 }	

	while(1) {
	printf("\ni)Insert\nd)delete\nm)Get Maximum Registered Courses\np)Print RegList\ne)Terminante");
	        printf("\n");
	        scanf("%s",character);
	        if(!strcmp(character,"i")){
	        scanf("%s %s",studentName,code);
	                insert(code, studentName, courseDetails, n);
	                continue;
	        }
	        else if(!strcmp(character,"d")){
	        scanf("%s %s",studentName,code);
                        delete (code, studentName, courseDetails, n);
	                continue;
	        }
	        else if(!strcmp(character,"m")) {
	                getMaxRegisteredCourse(courseDetails, n);
	                continue;
	        }
	        else if(!strcmp(character,"e")) {
	                break;
	        }else if(!strcmp(character,"p")) {
	                scanf("%s",code);
	                printRegList(code,courseDetails,n);
	                continue;
	        }
	        else{
	        printf("\nInvalid option\n");
	        break;
	       }
	
	}
	return 0;	
	
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
    if (!strcmp(courseDetails[i]->type,"elective")&&
        !(regListCount(courseDetails[i]->regList, 0) <
          courseDetails[i]->maxLimit)) // check maxLimit if course is elective.
    {
        printf("\n%s has reached MaxLimit,Student %s is inserting into Priority Queue.", coursename, studentname);
        //printf("\nEnter the Priority key: ");
        //scanf("%d", &key);
        key=courseDetails[i]->priority--;        
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



void delete (char coursename[], char studentname[], struct course *courseDetails[], int n){
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
    free(deletenode);

    // logic: after dequeue need to do insert operation..

    deQueueFlag = extract_Max(courseDetails[i]);
    if (deQueueFlag)
    { 
        printf("\nStudent %s extracted from the course %s Queue.", deQueueFlag->studentname, coursename);
        insert(coursename, deQueueFlag->studentname, courseDetails, n);
    }
    return;
}

void getMaxRegisteredCourse(struct course *Courses[],int n) {
        int maxCount=0;
        for(int i=0;i<n;i++){
                if(maxCount<regListCount(Courses[i]->regList, 0)){
                       maxCount=regListCount(Courses[i]->regList,0);
                }
        }
        for(int i=0;i<n;i++){
                if(maxCount==regListCount(Courses[i]->regList, 0)){
                        printf("%s ",Courses[i]->code);
                }
        }
return;
}

void Transplant(struct course *courseData, struct courseRegisterList *u,
                struct courseRegisterList *v){
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
    courseData->priority++;
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
    else
    { // inorder traversal of the reglist bst.
        printf("\n%s %s %d %s %d\n",courseDetails[i]->code,courseDetails[i]->name,
	courseDetails[i]->credits,courseDetails[i]->type,courseDetails[i]->maxLimit);
	if (!courseDetails[i]->regList)
        {
        printf("\nNo students have registered for the course %s", coursename);
        return;
        }
        inorderTreeWalk(courseDetails[i]->regList);
    }
    return;
}

