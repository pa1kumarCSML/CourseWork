#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;//noofcourses
int m;//noofedges in DAG
int getCourseIndex(char []);
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
    	struct adjacentList *preReq, *temp1;
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
    }
          

    return;
}





void getMaxPreRequisitesCourse() {

	int maxCount=0;
	int countsOfCourses[20];
	for(int i=0;i<n;i++){
		int count=0;
		struct adjacentList *curList = preReqList[i];
    		while (curList)
    		{	count++;
    			curList = curList->next;
        	}
        	countsOfCourses[i]=count;
		if(maxCount<count)
			maxCount=count;
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
    	while (1)
	{
        	fscanf(fptr,"%s",choose);
        	if (!strcmp(choose,"p"))
        	{
  			getMaxPreRequisitesCourse();
       		}
        	else 
        	{
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


















