#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct BST{
char student_id[10];
char student_name[20];
struct BST *left;
struct BST *right;
};

struct BST *head=NULL;

FILE *fp;


void insertStudentDetails(struct BST *s,struct BST *root){

        struct BST *parent;
       
        //insertion.
        if(root==NULL){
                head=s;
                return;
        }        

        while(root){
                if(strcmp(s->student_id,root->student_id)>0){
                        parent=root;
                        root=root->right;
                }
                else {
                        parent=root;
                        root=root->left;
                }        
        }
        
                if(strcmp(s->student_id,parent->student_id)>0){
                        parent->right=s;

                }
                else {
                        parent->left=s;

                }        
        return;
}



void printSortedList(struct BST *root){
        if(root==NULL)
                return;
                
        printSortedList(root->left);
        printf("\n%s %s",root->student_id,root->student_name);
        printSortedList(root->right);
}



int main() {

int n;
char option[1];

fp=fopen("input","r");
fscanf(fp,"%d",&n);
struct BST *s,*root;
for(int i=0;i<n;i++){    
        s=(struct BST *)malloc(sizeof(struct BST));
        fscanf(fp,"%s %s",s->student_id,s->student_name);
        s->left=NULL;
        s->right=NULL;    
        root=head;
        insertStudentDetails(s,root);
}

while(1){
fscanf(fp,"%s",option);

        if(!strcmp(option,"p")){
                printSortedList(head);
        }
        else{
                break;
        }
}


fclose(fp);
return 0;
}





