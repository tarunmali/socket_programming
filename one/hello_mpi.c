#include<stdio.h>
#include<mpi.h>
//Prints thread id out of total threads
int main(int argc,char **argv){
//argc->Argument count,argv->argument vector
int rank,size;
//From here MPI will start
//Note that argc and argv are passed by address.
MPI_Init(NULL,NULL);
//MPI_Comm_WORLD is predefined communicator in the MPI
//MPI_Get_processor_name(name,&length)
MPI_Comm_rank(MPI_COMM_WORLD,&rank);//MPI Common rank
MPI_Comm_size(MPI_COMM_WORLD,&size);//MPI Common size
printf("Hello MPI:processor %d out of %d\n",rank,size);
//Close the MPI
MPI_Finalize();
//Serial programming starts over here.
return 0;
}