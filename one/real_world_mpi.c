#include<mpi.h>
#include<stdio.h>

int main(int argc,char **argv){

//Initialize the MPI environment
MPI_Init(NULL,NULL);
//Get the number of processes
int world_size;
MPI_Comm_size(MPI_COMM_WORLD,&world_size);
//Get the rank of the process
int world_rank;
MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
//Get the name of the processor
char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;
MPI_Get_processor_name(processor_name,&name_len);
if(world_rank!=0){
char received_letter;
MPI_Recv(&received_letter,1,MPI_CHAR,world_rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
printf("City %d recevied letter %c from city %d\n",world_rank,received_letter,world_rank-1);
}
else{
//City 0 does not receive any letter
}

char sent_letter= 'A'+world_rank;
MPI_Send(&sent_letter,1,MPI_CHAR,(world_rank+1)%world_size,0,MPI_COMM_WORLD);
printf("City %d sent letter %c to city %d\n",world_rank,sent_letter,(world_rank+1)%world_size);

if(world_rank==0){
char received_letter;
MPI_Recv(&received_letter,1,MPI_CHAR,world_size-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
printf("City %d recieved letter %c from city %d\n",world_rank,received_letter,world_size-1);
}
// Finalize the MPI environment
MPI_Finalize();
return 0;
}