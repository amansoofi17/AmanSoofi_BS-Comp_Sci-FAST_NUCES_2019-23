#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//#define MAX_QUEUE_SIZE 19

int areAllVisited(int visited[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(visited[i] == 0)
			return 0;
	}
	return 1;
}

int main(int argc, char *argv[])
{
           clock_t start, end;
     double cpu_time_used;
	//Variables and Initializations
	int size, rank;
        int MAX_SIZE = 19;
        double t1, t2; 
	int adjacency_matrix[400]= {
  				    
        0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
	1,0,1,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,
	1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,
	0,1,1,0,0,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,
	0,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,0,0,0,0,
	0,0,1,1,0,0,1,1,0,1,0,0,0,1,1,0,0,0,0,0,
	0,0,0,1,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,0,
	0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
	0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,
	0,0,0,0,0,0,1,1,0,0,0,1,0,1,0,0,1,1,0,0,
	0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,0,1,0,1,
	0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,0,0,1,1,
	0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,
	0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0};


	int queue[MAX_SIZE];
	int source_vertex;
	int no_of_vertices = 20;
	int adjacency_row[20];
	int bfs_traversal[400];
	int visited[400];
	

	//MPI Code
	MPI_Init(&argc, &argv);
        t1 = MPI_Wtime();  
	start = clock();       
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0){

		//Entering the Source Vertex
		printf("Enter the Source Vertex\n");
		scanf("%d",&source_vertex);
		printf("\n");
	}

	//Broadcasting the Number of vertices and the source vertex;
	MPI_Bcast(&no_of_vertices, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&source_vertex, 1, MPI_INT, 0, MPI_COMM_WORLD);

	//Scattering each row of the adjacency matrix to each of the processes
	MPI_Scatter(adjacency_matrix, no_of_vertices, MPI_INT, adjacency_row, no_of_vertices, MPI_INT, 0, MPI_COMM_WORLD);

	//Initializing The Adjacency Queue of each process
	for(int i = 0; i < MAX_SIZE; i++)
	{
		queue[i] = -1;
	}

	//BFS code
	int index = 0;
	if(rank >= source_vertex)
	{
		for(int i = 0; i < no_of_vertices; i++)
		{
			if(adjacency_row[i] == 1)
			{
				queue[index++] = i;				
			}
		}
	}

	//Each Process printing the adjacent nodes found
        printf("\n\nProcess %d : ",rank);
	for(int i = 0; i < index; i++)
	{
		printf("%d ",queue[i]);
	}
        
	//For synchronization
	MPI_Barrier(MPI_COMM_WORLD);

	//Gathering all the nodes in BFS found by each process
	MPI_Gather(queue, MAX_SIZE, MPI_INT, bfs_traversal, MAX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

	
		t2 = MPI_Wtime();
        MPI_Barrier(MPI_COMM_WORLD);
        if(rank == 0)
{
end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("\n%lf",cpu_time_used);
}

	//printf( "\n\n\nElapsed time is %f\n", t2 - t1/ CLOCKS_PER_SEC ); 	
	
	//Printing the Order of traversed nodes in root
	for(int i = 0; i < no_of_vertices; i++)
	{
		visited[i] = 0;
	}

	if(rank == 0)
	{
		printf("\n\nBFS Traversal: \n");
		printf("%d",source_vertex);
		visited[source_vertex]=1;
		for(int i = 0; i < MAX_SIZE * no_of_vertices; i++)
		{
			//Exit Condition
			if(areAllVisited(visited, no_of_vertices))
			{
				break;
			}

			if(bfs_traversal[i] != -1)
			{
				if(visited[bfs_traversal[i]] == 0)
				{					printf(" -> %d ",bfs_traversal[i]);
					visited[bfs_traversal[i]] = 1;
				}
			}
			else
			{
				continue;
			}
		}
	}

	//End of BFS code 
	
	MPI_Finalize();
	return 0;


}

