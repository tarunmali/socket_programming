#include<stdio.h>
#include<omp.h>

int main(){
int id,total_threads;

//pragma omp parallel is a directive in OpenMP that creates a new team of threads to execute the block of code in parallel.

#pragma omp parallel
{
//Block of parallel programming
total_threads=omp_get_num_threads();// returns default no. of the core processor or the architecture.
id=omp_get_thread_num();// a library function for getting unique id
printf("Hello Ishaan Ashish Arora from thread %d out of %d threads\n",id,total_threads);
}
printf("Program exists\n");
return 0;
}