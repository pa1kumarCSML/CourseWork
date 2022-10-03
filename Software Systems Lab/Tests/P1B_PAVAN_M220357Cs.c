#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct diseases{
char disease[20];
char vaccine_adults[20];
char vaccine_child[20];
struct diseases *nextdisease;
};

struct diseases *HEAD=NULL;

void insert();
void print();
void delete();

int main(int argc, char **args){
	char character[1];
	while(1) {
	        printf("\n");
	        scanf("%s",character);
	        if(!strcmp(character,"i")){
	                insert();
	                continue;
	        }
	        else if(!strcmp(character,"d")){
	                delete();
	                continue;
	        }
	        else if(!strcmp(character,"p")) {
	                print();
	                continue;
	        }
	        else if(!strcmp(character,"s")) {
	                break;
	        }
	        else{
	        printf("\nInvalid option\n");
	        break;
	       }
	
	}
	return 0;	
	
}

void insert(){
        struct diseases *temp,*cur,*prev;
        cur=prev=HEAD;
        temp=(struct diseases *)malloc(sizeof(struct diseases));
        temp->nextdisease=NULL;
        scanf("%s %s %s",temp->disease,temp->vaccine_adults, temp->vaccine_child);
        
        if(!cur || (strcmp(temp->disease, cur->disease) < 0)){//insert at beggining.
                HEAD=temp;
                temp->nextdisease=cur;
        }
        else // if list is not empty.
        
        {  
                while (cur && strcmp(temp->disease, cur->disease) > 0) // at middle and at end of the list.
                {
                        prev = cur;
                        cur = cur->nextdisease;
                }
                temp->nextdisease = cur;
                prev->nextdisease = temp;
        } 
        return;
}

void print(){
        struct diseases *cur=HEAD;
        printf("\n");
        while(cur){
        printf("%s ",cur->disease);
        cur=cur->nextdisease;
        }
        return;
}


void delete() {
        char diseasename[20];
        struct diseases *cur,*prev;
        cur=prev=HEAD;
        scanf("%s",diseasename);
        if(!cur){
                printf("\nList is empty");
                return;
        }
        if(!strcmp(diseasename,cur->disease)){// deletion at beggining of the list.
                HEAD=cur->nextdisease;
                free(cur);
                return;
        }
        cur=cur->nextdisease;
        while(cur){// deletion at middle or at end of the list.
                if(!strcmp(diseasename,cur->disease)){
                        prev->nextdisease=cur->nextdisease;
                        free(cur);
                        return;
                }
                prev=cur;
                cur=cur->nextdisease;
        }
        if(!cur){
                printf("\nDisease not found!");
        }        

        return;
}

