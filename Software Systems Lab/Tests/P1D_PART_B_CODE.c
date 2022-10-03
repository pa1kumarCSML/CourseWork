#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;//noofcourses
int m;//noofedges in DAG
int stack[20];
int top=0;
int getCourseIndex(char []);

void getSucceedingCourses(char []);

void DFS(int i, int *visited);
struct course
{
    char code[20];
    char name[30];
};

struct adjacentList
{
    int courseIndex;
    struct adjacentList *next;
};

struct course *courseDetails[20];
struct adjacentList *preReqList[20];
struct adjacentList *Graph[20];

FILE *fptr;




void getData()
{

    int i = 0;
    fptr = fopen("input", "r");
    if (!fptr)
    {
        printf("Error!, File Not Found");
        exit(1);
    }
    
    fscanf(fptr, "%d",&n);

    fscanf(fptr,"%d",&m);

    for(int i=0;i<n;i++){
    courseDetails[i] = (struct course *)malloc(sizeof(struct course));
    fscanf(fptr,"%s",courseDetails[i]->code);
    
    char c;
    char name[30];int in=0;
    while((c=fgetc(fptr))!='\n'){
    	name[in++]=c;
    }
    name[in]='\0';
    strcpy(courseDetails[i]->name,name);
    
    }

    
    for(int i=0;i<m;i++){
    	char code1[10],code2[10];
    	int index1,index2;
    	struct adjacentList *preReq, *temp1,*temp,*cur;
    	fscanf(fptr,"%s %s",code1,code2);

    	index1=getCourseIndex(code1);
    	index2=getCourseIndex(code2);
    	temp1 = (struct adjacentList *)malloc(sizeof(struct adjacentList));
        temp1->next = NULL;
        temp1->courseIndex = index1;
        if (!preReqList[index2])
        {
            preReqList[index2] = temp1;
        }
        else
         {
            temp1->next=preReqList[index2];
            preReqList[index2] = temp1;
         }
         
             	
         temp = (struct adjacentList *)malloc(sizeof(struct adjacentList));
         temp->next = NULL;         
         temp->courseIndex = index2;
         
         if (!Graph[index1])
         {
             Graph[index1] = temp;
         }
         else
         {
             cur = Graph[index1];
             while (cur->next)
             {
                cur = cur->next;
             }
             cur->next = temp;
             cur = cur->next;
        }
    }
          

    return;
}





void getMaxPreRequisitesCourse() {

	int maxCount=0;// initially max is 0
	int countsOfCourses[20];
	for(int i=0;i<n;i++){// for get the counts of prereqs of all courses
		int count=0;
		struct adjacentList *curList = preReqList[i];
    		while (curList)//traversing the linkedlist of each course prereqs.
    		{	count++;
    			curList = curList->next;
        	}
        	countsOfCourses[i]=count; //storing count value
		if(maxCount<count)
			maxCount=count;// update everytime
	}       	
		
	for(int i=1;i<n;i++){
		if(countsOfCourses[i]==maxCount)
			printf("%s ",courseDetails[i]->code);
	}
	return;
}









int main() {

	getData();
	char choose[1];
	char code[10];
    	while (1)
	{
        	fscanf(fptr,"%s",choose);
        	if (!strcmp(choose,"p"))
        	{
  			getMaxPreRequisitesCourse();
       		}
        	else if(!strcmp(choose,"t"))
        	{
        		fscanf(fptr,"%s",code);
        		getSucceedingCourses(code);
        	}
        	else{
         	 break;
        	}
	}
	    fclose(fptr);
return 0;
}


int getCourseIndex(char code[])
{
    int i = 0;
    for (; i < n; i++) // to get the course index..
    {
        if (!strcmp(courseDetails[i]->code, code))
        {
            break;
        }
    }
    if (i == n)
    {
        printf("\nCourse not found!!");
        return -1;
    }
    return i;
}


void DFS(int i, int *visited)
{
    visited[i] = 1;
    struct adjacentList *cur;
    cur = Graph[i];
    while (cur)
    {
        if (visited[cur->courseIndex] == 0)
        {
            DFS(cur->courseIndex, visited);
        }
        cur = cur->next;
    }
    stack[top++] = i;
    return;
}


void getSucceedingCourses(char code[]){
	int indexOfCourse;
	int visited[20];
	for(int i=0;i<n;i++){
		visited[i]=0;
	}
	
	indexOfCourse=getCourseIndex(code);
	DFS(indexOfCourse,visited);
	printf("\n");
	top--;
	while (top){
        	printf("%s ", courseDetails[stack[--top]]->code);
   	}
	return;
}















