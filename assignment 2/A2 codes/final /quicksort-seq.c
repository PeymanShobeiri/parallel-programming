#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MASTER 0        /* tas id of master task */

// Function declarations
void swap(int* a, int* b);
int partition (int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void printArray(int arr[], int size, bool demo_mode);


// Main func
int main (int argc, char *argv[])
{
int	taskid;         /* task ID - used as seed number */
int numtasks;       /* number of tasks */

bool demo_mode = false; // Toggle between demo and test modes


double start, end; 

/* Obtain number of tasks and task ID */
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);

printf ("MPI task %d has started...\n", taskid);

MPI_Barrier(MPI_COMM_WORLD); 
if(taskid == MASTER)
    start = MPI_Wtime();

{
    int n = sizeof(random_array_seq)/sizeof(random_array_seq[0]); 
    printf("\nUnsorted array: ");
    printArray(random_array_seq, n, demo_mode);

    quickSort(random_array_seq, 0, n-1);

    printf("\nSorted array: ");
    printArray(random_array_seq, n, demo_mode);
}

MPI_Barrier(MPI_COMM_WORLD); 
if (taskid == MASTER) {
    end = MPI_Wtime();
    printf("Runtime = %f\n", end-start);
}

MPI_Finalize();
return 0;
}

/*
    Code below is from the website https://www.geeksforgeeks.org/quick-sort/
*/

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function
int partition(int arr[], int low, int high) {
    
    // Choose the pivot
    int pivot = arr[high];
    
    // Index of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements to the left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Move pivot after smaller elements and
    // return its position
    swap(&arr[i + 1], &arr[high]);  
    return i + 1;
}

// The QuickSort function implementation
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print an array with demo/test mode toggle
void printArray(int arr[], int size, bool demo_mode)
{
    int numbers_per_line = 10; // Controls numbers per line in demo mode
    
    if (demo_mode) {
        // Demo mode: Display with multiple numbers per line
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
            // Print a newline after every 'numbers_per_line' elements
            if ((i + 1) % numbers_per_line == 0) {
                printf("\n");
            }
        }
        // Add a final newline if the last line wasn't complete
        if (size % numbers_per_line != 0) {
            printf("\n");
        }
    } else {
        // Test mode: Display all numbers on a single line
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}
