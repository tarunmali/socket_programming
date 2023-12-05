#include<mpi.h>
#include<stdio.h>

int main(int argc,char **argv){

MPI_Init(NULL,NULL);

int world_size;
MPI_Comm_size(MPI_COMM_WORLD,&world_size);
int world_rank;
MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);

if(world_rank!=0){
  int received_token;
  MPI_Recv(&received_token,1,MPI_INT,world_rank-1,world_rank-1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  printf("Process %d recieved token %d from process %d\n",world_rank,received_token,world_rank-1);
}
else{
  //Process 0 does not receive any message
}
int sent_token=world_rank;//Send the rank as the token
MPI_Send(&sent_token,1,MPI_INT,(world_rank+1)%world_size,world_rank,MPI_COMM_WORLD);
printf("Process %d sent token %d to process %d\n",world_rank,sent_token,(world_rank+1)%world_size);

//Now process 0 can receive from the last process.

if(world_rank==0){
int received_token;
 MPI_Recv(&received_token,1,MPI_INT,world_rank-1,world_rank-1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  printf("Process %d recieved token %d from process %d\n",world_rank,received_token,world_rank-1);
}
MPI_Finalize();
return 0;
}