#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
void srandom (unsigned seed);

int main(int argc, char *argv[]){

#define sqr(x)	((x)*(x))
long random(void);
double x_coord, y_coord, pi,r,avepi;
int score,k, n, darts, rounds, tasks, i, taskid;
double start_time,end_time;
unsigned int cconst;  /* must be 4-bytes in size */

darts=50000;
rounds=100;
start_time= MPI_Wtime();
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

if (sizeof(cconst) != 4) {
   printf("Wrong data size for cconst variable in dboard routine!\n");
   printf("See comments in source file. Quitting.\n");
   exit(1);
   }

   cconst = 2 << (31 - 1);
   srandom(taskid);
   avepi = 0;

for (i = 0; i < rounds; i++) {

   score=0;

   for (n = 1; n <= darts; n++)  {

      r =(double)random()/cconst;
      x_coord = (2.0 * r) - 1.0;

      r =(double)random()/cconst;
      y_coord = (2.0 * r) - 1.0;

      if ((sqr(x_coord) + sqr(y_coord)) <= 1.0)
           score++;
      }

      pi = 4.0 * (double)score/(double)darts;
      avepi = ((avepi * i) + pi)/(i + 1);
      printf("After %d throws, average value of pi = %10.8f\n",(darts * i),avepi);
}

printf("After %d throws, average value of pi = %10.8f\n",(darts * rounds),avepi);

end_time = MPI_Wtime();
printf("The total time for this programme is %f seconds \n", end_time - start_time);

MPI_Finalize();
return 0;
}
