#include<stdio.h> 
#include <stdlib.h> 
#include<unistd.h>
#include<stdbool.h>

//Global Variables
int i=0,j=0,ind=0,num_process=0,num_resources=0;
int **alloc,**max,**need,*avail,*safe_sequence;


//function declaration
void Data(void);
void display_data(void);
void calculate_need(void);
bool check(int);
bool check_safe_sequence(int);
void change_available(int);
void start_Algorithm(void);

//queue
struct queue {
	int front;
	int rear;
	int *data;
	int itemCount;
}waiting_queue,ready_queue;


void push(struct queue *q1,int num ) {
	//num_process
	if (q1->itemCount != num_process)	// if not full
	{
		if (q1->itemCount == 0) {		//if empty
			q1->data = (int) calloc(num_process,sizeof(int));
			q1->front = 0;
			q1->rear = -1;
		}
		q1->rear++;
		q1->data[q1->rear] = num;
		q1->itemCount++;
	}
}

int pop(struct queue *q1) {
	int temp = 0;
	if (q1->itemCount != 0)		//if not empty
	{
		temp = q1->data[q1->front++];
		q1->itemCount--;
	}
	return temp;
}

//stating program
void Data(){
	printf("\n\n\n\t\t\t\t~~~~~~~~~~~~~~~Banker's Algorithm~~~~~~~~~~~~~~~\n\n");
	printf("Enter the number of processes: ");
	scanf("%d",&num_process);
	waiting_queue.itemCount = 0;
	
	// waiting queue
	for(i = 0;i<num_process;i++)
	{
		printf("Process %d loads into the waiting queue: \n",i+1);
	   	push(&waiting_queue,i);	
	   	sleep(1);
	}
	printf("\n\nEnter the number of resources: ");
	scanf("%d",&num_resources);
	printf("Enter the total available number of resources for each resourse:\n");
	int total_available_resources[num_resources];
	FILE* fp;
	fp = fopen("initial_alloc.txt","r");
	FILE* fp1; 
	fp1 = fopen("max_need.txt","r");
	for(i=0;i<num_resources;i++)
	{
		printf("For resource %d: ",i+1);
	    scanf("%d",&total_available_resources[i]);	
	}
	
	alloc=(int **) calloc(num_process,sizeof(int *));
	
	for(i=0;i<num_process;i++){
		
		alloc[i]=(int *)calloc(num_resources,sizeof(int *));
	}
	
	max=(int **) calloc(num_process,sizeof(int*));
	
	for(i=0;i<num_process;i++){
		
		max[i]=(int *) calloc(num_resources,sizeof(int*));
	}
	
	need=(int **) calloc(num_process,sizeof(int*));
	
	for(i=0;i<num_process;i++)	{
		
		need[i]=(int *) calloc(num_resources,sizeof(int*));
	}
	
	avail=(int *) calloc(num_resources,sizeof(int*));
	
	safe_sequence=(int *) calloc(num_process,sizeof(int*));
	
	display_data();
	
	printf("\n\nEnter the resouces allocated to each process:\n");
	
	for(i=0;i<num_process;i++){
		
		for(j=0;j<num_resources;j++){
			
			printf("%d-Process:",i+1);
			fscanf(fp, "%d", &alloc[i][j]);
			total_available_resources[j] = total_available_resources[j] - alloc[i][j];
		}
	}
	fclose(fp);
	display_data();
	
	printf("\n\nEnter the maximum required resoucres for each process:\n");
	
	for(i=0;i<num_process;i++){
		
		for(j=0;j<num_resources;j++){
			
			printf("%d-Process:",i+1);
				fscanf(fp1, "%d", &max[i][j]);
		}
	}
	fclose(fp1);
	display_data();
	
	printf("\n\nEnter the available resoucres:\n");
	
	for(i=0;i<num_resources;i++){
		
		*(avail+i) = total_available_resources[i];
	}
}

//displaying all data
void display_data(){
	
	system("cls");
	printf("\t\t~~~~~~~~~~~~~~Banker's Algorithm~~~~~~~~~~~~~~~\n\n");
	printf("\t |Processes| \t |Allocation| \t |Maximum| \t |Need| \t |Available| \n\n");
	
	for(i=0;i<num_process;i++){
		
		printf("\t      P%d \t  [",i+1);
		
		for(j=0;j<num_resources;j++)
			printf(" %d",alloc[i][j]);
		
		printf(" ]\t [");	
		
		for(j=0;j<num_resources;j++)
			printf(" %d",max[i][j]);
				
		printf(" ]\t [");	
		
		for(j=0;j<num_resources;j++)
			printf(" %d",need[i][j]);
		
		printf(" ]\t");
		
		if(i==0){
			
			printf("  [");
			for(j=0;j<num_resources;j++)
				printf(" %d",avail[j]);
			printf(" ]");
		}
		printf("\n");
	}
}

//calculating need matrix
void calculate_need(){
	
	for(i=0;i<num_process;i++){
		
		for(j=0;j<num_resources;j++){
			
			if ((max[i][j]-alloc[i][j]) < 0)	{
				printf("Maximum Value has bad input!");
				exit(0);
			}	else
				need[i][j]=max[i][j]-alloc[i][j];
		}
	}
}

//check condition
bool check(int k){
	
	for(j=0;j<num_resources;j++){
		
		if(need[k][j] > avail[j])
			return false;
	}
	return true;
}


//check in safe sequence
bool check_safe_sequence(int k){
	
	for(j=0;j<num_process;j++){
					
		if(k == safe_sequence[j]-1)
			return true;
	}
	return false;
}

//updating available resources
void change_available(int k){
	
	printf("\nAvailable: [ ");

	for(j=0;j<num_resources;j++){
		
		avail[j]=avail[j]+alloc[k][j];
		printf("%d ", avail[j]);

	}

	printf("]\n");
}

//starting algorithm
void start_Algorithm(){
	
	int k = 0,verify = 0;
	
	while(1){
		for(i=0;i<num_process;i++){
			
			verify=1;
			int temp = pop(&waiting_queue);
			if(check_safe_sequence(temp))
				continue;
			
			 if(check(temp)){
				verify=0;
				printf("P%d- ",temp+1);
				printf("Need < Word!\n");
				safe_sequence[ind]=temp+1;
				ind++;
				change_available(temp);
				push(&ready_queue,temp);
			}
			else{
				push(&waiting_queue,temp);
				printf("P%d- ",temp+1);
				printf("Need > Word!\n");
			}
			//system("pause");			
		}
		if(verify==1)
			break;
	}
	
	for(i=0;i<num_process;i++)	{
		
		if (safe_sequence[i] == 0)	{
			printf("Safe sequence not found because one or more process is not getting the required resources!\n");
			exit(0);
		}
	}
    
	printf("\n\n\n");
	for(i=0;i<num_process;i++)
	{
		printf("Process %d is ready to execute: \n",pop(&ready_queue)+1);
		sleep(1);
	}
	printf("\n");
}

void main(){
	
	Data();
	display_data();
	calculate_need();
	display_data();
	start_Algorithm();
}
