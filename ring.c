/* C Example */
#include <mpi.h>
#include <stdio.h>
 
int main (int argc, char* argv[])

{
  int rank, size; 
  int data, data_r,n;
  data_r=0;
  MPI_Init (&argc, &argv);       
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);       
  MPI_Comm_size (MPI_COMM_WORLD, &size);        
  printf( "Hello world from process %d of %d\n -----\n", rank, size );
  MPI_Status status;
  MPI_Request request;
  int data_suma;


  data = rank;
  data_suma=data;
  
        for (n=0; n<size-1; n++){
            MPI_Isend(&data, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD,&request); 
                      
            printf("Process %d sending number: %d\n",rank, data);

            MPI_Recv(&data_r, 1, MPI_INT, (rank-1+size)%size, 0, MPI_COMM_WORLD,&status);
            MPI_Wait(&request,MPI_STATUS_IGNORE); 
            data=data_r;
            data_suma=data_suma+data_r;
                             }
        
        printf("Process %d receiving number: %d\n",rank, data_r);
        
        printf("Sum= %d\n",data_suma);



MPI_Finalize();
return 0;

}
