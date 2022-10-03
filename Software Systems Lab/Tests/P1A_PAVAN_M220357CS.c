#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct diseases{
int serial_number;
char disease[20];
char vaccine_adults[20];
char vaccine_child[20];
};

void listVaccines(struct diseases [],char [], int);

FILE *fptr;

int main(int argc, char **args){
	struct diseases diseaseList[20];
	int n;
	char vaccine_name[20];
	scanf("%d",&n);// no of diseases
	for(int i=0;i<n;i++){//each disease details
	        scanf("%d %s %s %s",&diseaseList[i].serial_number,
	        diseaseList[i].disease,diseaseList[i].vaccine_adults,
	        diseaseList[i].vaccine_child);
	}
	scanf("%s",vaccine_name);// vaccinename
	listVaccines(diseaseList,vaccine_name,n);	
	
}


void listVaccines(struct diseases diseaseList[],char vaccine_name[], int n){
	int flag=0;
	fptr=fopen("diseases.txt","w");
	if(!fptr){
		printf("Error!!");
		exit(1);
		}
        for(int i=0;i<n;i++){
                if(!strcmp(diseaseList[i].vaccine_adults,vaccine_name) ||
                        !strcmp(diseaseList[i].vaccine_child,vaccine_name)) {
                        fprintf(fptr, "%s\n", diseaseList[i].disease);
                        flag=1;
                }
                        
        }
        if(!flag){
                fprintf(fptr, "%s\n","NIL");
        }
	
	fclose(fptr);
	return;
}








