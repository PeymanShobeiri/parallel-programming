#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <time.h>

void srandom (unsigned seed);
double dboard (int darts);

#define DARTS 50000
#define ROUNDS 100
#define MASTER 0

int main (int argc, char *argv[])
{

double  homepi,         /* value of pi calculated by current task */
        pisum,          /* sum of tasks' pi values */
        pi,             /* average of pi after "darts" is thrown */
        avepi;          /* average pi value for all iterations */
int     taskid,         /* task ID - also used as seed number */
        numtasks,       /* number of tasks */
        rc,             /* return code */
        commtasks,
        i;
double start_time, end_time;
start_time = MPI_Wtime();;
    MPI_Comm slaves;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

    if ( argc != 2 )
        printf( "usage: %s <number of workers>\n", argv[0] );
    else
        numtasks = atoi( argv[1] );

    printf ("Master task id is: %d. Total tasks in master comm are: %d \n", taskid, numtasks);

// int MPI_Comm_spawn(const char *command, char *argv[], int maxprocs, MPI_Info info, int root, MPI_Comm comm, MPI_Comm * intercomm, int array_of_errcodes[])
MPI_Comm_spawn( "pi_slave_code.o", argv, numtasks, MPI_INFO_NULL, 0, MPI_COMM_SELF, &slaves, MPI_ERRCODES_IGNORE );

srandom (taskid);

avepi = 0;
for (i = 0; i < ROUNDS; i++) {

   rc = MPI_Reduce(&homepi, &pisum, 1, MPI_DOUBLE, MPI_SUM, MPI_ROOT, slaves);
   pi = pisum/numtasks;
   avepi = ((avepi * i) + pi)/(i + 1);

}
    end_time = MPI_Wtime();;
    printf("   After %8d throws, average value of pi = %10.8f\n",(DARTS * ROUNDS),avepi);
    printf("The total time for this programme is %f seconds \n", end_time - start_time);
    MPI_Finalize();

    return 0;
}
