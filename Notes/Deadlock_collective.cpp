#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int i, j, a, b;
    int array[10], buf[10];
    int rank, size;
    float Sum = 0;
    float S = 0;
    double time_start, time_finish;
    
    MPI_Status Status;
    MPI_Request Request;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

//--------- Deadlock -----------------------

    //if (rank == 0) {
    //    a = 0;
    //    b = 10;
    //    //MPI_Irecv(&b, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &Request);

    //    //MPI_Recv(&b, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &Status);
    //    //MPI_Send(&a, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);

    //    MPI_Sendrecv(&a, 1, MPI_INT, 1, 1, 
    //                 &b, 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &Status);
    //}
    //if (rank == 1) {
    //    a = 1;
    //    b = 11;
    //    //MPI_Irecv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &Request);
    //    
    //    //MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &Status);
    //    //MPI_Send(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);

    //    MPI_Sendrecv(&a, 1, MPI_INT, 2, 1,
    //                 &b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &Status);
    //}
    //if (rank == 2) {
    //    a = 2;
    //    b = 12;
    //    MPI_Sendrecv(&a, 1, MPI_INT, 0, 1,
    //                 &b, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &Status);
    //}
    //
    //printf("I am %d, a = %d, received b = %d \n", rank, a, b);

//--------- end of Deadlock -----------------------


//--------- ANY SOURCE ----------------------------

    /*if (rank == 0) {
        for (i = 1; i < size; i++) {
            MPI_Recv(&b, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &Status);
            printf("b = %d, from rank %d \n", b, Status.MPI_SOURCE);
        }
    }
    if (rank != 0) {
        b = rank;
        MPI_Send(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }*/

//--------- end of ANY SOURCE ---------------------


//--------- MPI_Probe -----------------------------
    
    //if (rank == 0) {
    //    a = 10;
    //    //MPI_Send(&a, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
    //    array[1] = 100;
    //    MPI_Send(&array[0], 5, MPI_INT, 1, 1, MPI_COMM_WORLD);
    //}

    //if (rank == 1) {
    //    int count;
    //    MPI_Probe(0, 1, MPI_COMM_WORLD, &Status);
    //    MPI_Get_count(&Status, MPI_INT, &count);

    //    printf("Count = %d \n", count);
    //    MPI_Recv(array, count, MPI_INT, 0, 1, MPI_COMM_WORLD, &Status);
    //    printf("Array[1] = %d \n", array[1]);
    //}

//--------- end of MPI_Probe ----------------------


//--------- MPI_Barrier -----------------------

    //MPI_Barrier(MPI_COMM_WORLD);
    //time_start = MPI_Wtime();
    ////printf("I am %d of %d, start = %f \n", rank, size, time_start);

    //for (i = 1; i <= 1000000; i++) {
    //    Sum = Sum + 1;
    //}
    //
    //if (rank != 0) MPI_Send(&Sum, 1, MPI_FLOAT, 0, rank, MPI_COMM_WORLD);
    //
    //if (rank == 0) {
    //    for (i = 1; i < size; i++) {
    //        MPI_Recv(&S, 1, MPI_FLOAT, i, i, MPI_COMM_WORLD, &Status);
    //        Sum = Sum + S;
    //    }
    //    printf("All Sum = %f \n", Sum);
    //}
    //printf("\n");
    //MPI_Barrier(MPI_COMM_WORLD);
    //time_finish = MPI_Wtime();
    //printf("I am %d of %d, finish = %f \n", rank, size, time_finish);

//--------- end of MPI_Barrier -----------------------
   

//--------- MPI Bcast -----------------

   /* if (rank == 0) {
        for (i = 0; i < 10; i++) {
            array[i] = i;
        }
        MPI_Bcast(&array[5], 5, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if (rank != 0) {
        printf("Before broadcasting \n");
        for (i = 0; i < 10; i++) {
            printf("%d   ", array[i]);
        }
        printf("\n");

        MPI_Bcast(&array[5], 5, MPI_INT, 0, MPI_COMM_WORLD);
        
        printf("After broadcasting \n");
        for (i = 0; i < 10; i++) {
            printf("%d   ", array[i]);
        }
        printf("\n");
    }*/

//--------- MPI Bcast -----------------

//--------- MPI Scatter -----------------
    
    /*if (rank == 0) {
        for (i = 0; i < 10; i++) {
            array[i] = i;
        }

        printf("Before scatter process %d \n", rank);
        for (i = 0; i < 10; i++) {
            printf("%d   ", buf[i]);
        }
        printf("\n");
       
        MPI_Scatter(array, 3, MPI_INT, buf, 3, MPI_INT, 0, MPI_COMM_WORLD);

        printf("After scatter process %d \n", rank);
        for (i = 0; i < 10; i++) {
            printf("%d   ", buf[i]);
        }
        printf("\n");
    }

    if (rank != 0) {
        printf("Before scatter process %d \n", rank);
        for (i = 0; i < 10; i++) {
            printf("%d   ", buf[i]);
        }
        printf("\n");

        MPI_Scatter(array, 3, MPI_INT, buf, 3, MPI_INT, 0, MPI_COMM_WORLD);
        
        printf("After scatter process %d \n", rank);
        for (i = 0; i < 10; i++) {
            printf("%d   ", buf[i]);
        }
        printf("\n");
    }*/

//--------- MPI Scatter -----------------


//--------- MPI Gather -----------------

    /*if (rank == 0) {
        for (i = 0; i < 10; i++) {
            array[i] = rank;
        }

        printf("Before gather process %d \n", rank);
        for (i = 0; i < 10; i++) {
            printf("%d   ", buf[i]);
        }
        printf("\n");
        MPI_Gather(array, 3, MPI_INT, buf, 3, MPI_INT, 0, MPI_COMM_WORLD);

        printf("After gather process %d \n", rank);
        for (i = 0; i < 10; i++) {
            printf("%d   ", buf[i]);
        }
        printf("\n");
    }

    if (rank != 0) {
        for (i = 0; i < 10; i++) {
            array[i] = rank;
        }
        printf("\n");

        MPI_Gather(array, 3, MPI_INT, buf, 3, MPI_INT, 0, MPI_COMM_WORLD);
    }*/

//--------- MPI Gather -----------------


//--------- MPI Reduce -----------------
    
    if (rank == 0) {
        for (i = 0; i < 10; i++) {
            array[i] = i;
        }

        printf("Before reduce process %d \n", rank);
        for (i = 0; i < 10; i++) {
            printf("%d   ", buf[i]);
        }
        printf("\n");

        //MPI_Reduce(array, buf, 5, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Allreduce(array, buf, 5, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

        printf("After reduce process %d \n", rank);
        for (i = 0; i < 10; i++) {
            printf("%d   ", buf[i]);
        }
        printf("\n");
    }

    if (rank != 0) {
        for (i = 0; i < 10; i++) {
            array[i] = i;
        }
        printf("\n");

        //MPI_Reduce(array, buf, 5, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Allreduce(array, buf, 5, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

        printf("After reduce process %d \n", rank);
        for (i = 0; i < 10; i++) {
            printf("%d   ", buf[i]);
        }
        printf("\n");
    }

//--------- end MPI Reduce -------------

    MPI_Finalize();
}

