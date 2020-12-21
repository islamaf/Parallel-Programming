#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define arr_n 1000000
int res_arr[10000000];

//int *res_arr = (int*) malloc(arr_n * sizeof(int));

int main(int argc, char *argv[]){
    int i;
    int array[arr_n];
    //long long int *array;
    //array = (long long int*) malloc(arr_n * sizeof(long long int));

    //long long int *res_arr;
    //res_arr = (long long int*) malloc(arr_n * sizeof(long long int));

    int myrank, size;
    int send, recv, n_process;

    MPI_Status Status; //mpi data type

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    int part_per_process = arr_n/size;
    long long sum = 0;

    printf("I am %d of %d\n", myrank, size);
    double begin, end, total;

    MPI_Barrier(MPI_COMM_WORLD);
    if(myrank==0){
        begin = MPI_Wtime();
    }

    //begin = MPI_Wtime();
    if(myrank == 0){
        //array = malloc(arr_n * sizeof(long long int));
        //res_arr = malloc(arr_n * sizeof(long long int));

        for(i=0; i<=arr_n; i++){
            array[i] = i;
        }
        
//      begin = MPI_Wtime();

        int k;
        for(k=1; k < size-1; k++){
            send = part_per_process * k;
            MPI_Send(&part_per_process, 1, MPI_INT, k, 0, MPI_COMM_WORLD);
            MPI_Send(&array[send], part_per_process, MPI_INT, k, 0, MPI_COMM_WORLD);
        }

        send = part_per_process * k;

        //printf("k is %d\n", k);
        if(size > 1){
            int elements_left = arr_n - send;
        //    printf("elements_left are %d and send is %d\n", elements_left, send);
            MPI_Send(&elements_left, 1, MPI_INT, k, 0, MPI_COMM_WORLD);
        //    printf("something\n");
            MPI_Send(&array[send], elements_left, MPI_INT, k, 0, MPI_COMM_WORLD);
        //    printf("send failed\n");
        }

        for(i = 0; i < part_per_process; i++){
            sum += array[i];
        }

        long long tmp = 0;
        for(i=1; i < size; i++){
            MPI_Recv(&tmp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &Status);

            sum += tmp;
        }

        printf("sum of array is %lld\n", sum);
    }else{
        //res_arr = (long long int*) realloc(res_arr, arr_n);
        //if(myrank != size-1){
        //MPI_Recv(&recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &Status);
        //MPI_Recv(&res_arr, recv, MPI_INT, 0, 0, MPI_COMM_WORLD, &Status);
        //}

        MPI_Recv(&recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &Status);
        //res_arr = malloc(arr_n * sizeof(long long int));
        MPI_Recv(&res_arr, part_per_process, MPI_INT, 0, 0, MPI_COMM_WORLD, &Status);

        //printf("recv is %d for rank %d\n", recv, myrank);

        long long part_sum = 0;
        int j;

        //printf("initial part_sum is %d\n", part_sum);

        for(j=0; j < recv; j++){
            array[j] = j;
            part_sum += array[j];
        //    printf("part_sum here is %d at j=%d\n", part_sum, j);
        }

        //int k;
        //if(myrank == 3){
        //    for(k=0; k<recv; k++){
        //      if(res_arr[k] < 0){
        //          printf("value is %d\n", res_arr[k]);
        //      }
        //    }
        //}

        //printf("recv is %d for rank %d\n", recv, myrank);
        printf("This sum is %lld for rank %d\n", part_sum, myrank);
        MPI_Send(&part_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

//    MPI_Barrier(MPI_COMM_WORLD);
//    end = MPI_Wtime();

//    MPI_Finalize();

    if(myrank == 0){
        end = MPI_Wtime();
        total = end-begin;
        printf("Total is %.5f\n", total);
    }

    //free(array);
    //free(res_arr);

    MPI_Finalize();

    return 0;
}
                            
