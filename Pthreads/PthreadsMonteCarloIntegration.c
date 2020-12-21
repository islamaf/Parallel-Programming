#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

int num_threads=1, data_pts=1000000000;
//double *all_counts = (double*) malloc(sizeof(double));
//*all_counts = 0.0;
double all_counts = 0.0;
double pi = 3.14159265358;
sem_t sem;

void *func(void *tid){
    long thid = (long)tid;
    int tid1 = (int)thid;
    //int thid;
    //thid = (double) *(int*)tid;

    //double *circ_count = (double *) malloc(sizeof(double));
    //*circ_count = 0.0;

    double circ_count = 0.0;

    double iter = data_pts/(double) num_threads;

    unsigned int x_k, y_k, z_k;
    srand(time(NULL)/(thid+1));
    x_k = rand();
    y_k = rand();
    z_k = rand();

    int c;
    for(c = 0; c < iter; c++){
        double x = (((double)rand_r(&x_k))/RAND_MAX)*pi;
        double y = (((double)rand_r(&y_k))/RAND_MAX);
        double z = (((double)rand_r(&z_k))/RAND_MAX)*pi;
        if(x<=pi && y <= sin(x)){
//          sem_wait(&sem);
                circ_count += x*y;
//          sem_post(&sem);
        }
    }

    sem_wait(&sem);
    all_counts += circ_count;
    sem_post(&sem);
    
    double *return_circ_count = (double*) malloc(sizeof(double));
    *return_circ_count = circ_count;

    pthread_exit(NULL);
}

int main(){
    sem_init(&sem, 0, 1);
    struct timespec begin, end;
    double elapsed;

//    time_t t;
    long i;
    //srand((unsigned) time(&t));

    pthread_t threads[num_threads];
    int rc;
    void *status;
    double tot_circle = 0;
//    int i;

    clock_gettime(CLOCK_REALTIME, &begin);
    for(i=0; i<num_threads; i++){
        rc = pthread_create(&threads[i], NULL, func, (void*)i);
        if(rc){
            printf("error code: %d", rc);
            exit(-1);
        }
    }

    for(i=0; i<num_threads; i++){
        pthread_join(threads[i], &status);
//      all_counts += *(double*)status;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = end.tv_sec - begin.tv_sec;
    elapsed += (end.tv_nsec - begin.tv_nsec)/1000000000.0;

    printf("Time is %lf\n", elapsed);
    printf("Value of Pi: %f", (pi*all_counts/data_pts));

    pthread_exit(NULL);
    sem_destroy(&sem);
    return 0;
}
