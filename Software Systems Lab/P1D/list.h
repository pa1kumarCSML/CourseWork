#include "queue.h"

void insert(char[], char[], struct course *[], int);
void delete (char[], char[], struct course *[], int);
void inorderTreeWalk(struct courseRegisterList *);
void printRegList(char[], struct course *[], int);
void inorderTreeWalkWithStack(struct courseRegisterList *);
void createDAG(struct course *[], int);
void topologicalSortUsingDFS(struct course *[], int);
void topologicalSortUsingKhansAlgo(struct course *[], int);
