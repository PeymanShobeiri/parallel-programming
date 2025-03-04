#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>


void srandom (unsigned seed);
double dboard (int darts);

#define DARTS 50000     /* number of throws at dartboard */
#define ROUNDS 100      /* number of times "darts" is iterated */
#define MASTER 0        /* task ID of master task */

int main (int argc, char *argv[]){
double  homepi,         /* value of pi calculated by current task */
        pisum,          /* sum of tasks' pi values */
        pi,             /* average of pi after "darts" is thrown */
        avepi;          /* average pi value for all iterations */
int     taskid,         /* task ID - also used as seed number */
        numtasks,       /* number of tasks */
        rc,             /* return code */
        i;

double start_time, end_time;
start_time = MPI_Wtime();

MPI_Status status;

MPI_Comm master;
MPI_Init(&argc,&argv);

MPI_Comm_get_parent(&master);

if(master == MPI_COMM_NULL){
   printf("No master (parent) found");
   exit(1);
}


MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
printf ("MPI task %d has started...\n", taskid);

srandom (taskid);

avepi = 0;
for (i = 0; i < ROUNDS; i++) {
   homepi = dboard(DARTS/numtasks);

   rc = MPI_Reduce(&homepi, &pisum, 1, MPI_DOUBLE, MPI_SUM, MASTER , master);
   }

   end_time = MPI_Wtime();
   printf("Time for the Slave is : %f seconds \n", end_time - start_time);
   MPI_Finalize();
   return 0;
}


double dboard(int darts) {
#define sqr(x)  ((x)*(x))

        long random(void);
double x_coord, y_coord, pi, r;
int score, n;
unsigned int cconst;  /* must be 4-bytes in size */

if (sizeof(cconst) != 4) {
   printf("Wrong data size for cconst variable in dboard routine!\n");
   printf("See comments in source file. Quitting.\n");
   exit(1);
   }
   cconst = 2 << (31 - 1);
   score = 0;

   for (n = 1; n <= darts; n++)  {
      r = (double)random()/cconst;
      x_coord = (2.0 * r) - 1.0;
      r = (double)random()/cconst;
      y_coord = (2.0 * r) - 1.0;

      if ((sqr(x_coord) + sqr(y_coord)) <= 1.0)
           score++;
      }

pi = 4.0 * (double)score/(double)darts;
return(pi);
}
