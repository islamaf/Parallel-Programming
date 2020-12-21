#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<omp.h>

using namespace std;

int main(int argc, char* argv[]){

#ifdef _OPENMP
	printf("OpenMP is supported! %d \n", _OPENMP);
#endif

	int a[20];
	int i = 0;
	int j = 0;
	int myid;
	long const N = 1e8;
	int num_threads, num, num_procs, max_thr;

	double integral, s, S, dx;
	double t_in, t_out;

	printf("dx = %f \n", dx);
	
	max_thr = omp_get_max_threads();
	num_procs = omp_get_num_procs();

	printf("Max threads = %d \n", max_thr);
	printf("Num of processors = %d \n", num_procs);

	printf("----------------------------\n");
	
	omp_set_num_threads(2);
	
	num_threads = omp_get_num_threads();  // получение кол-ва работающих в данный момент нитей
	printf("Now num of threads = %d \n", num_threads);

	s = 0.0;
	S = 0.0;
	integral = 0.0;
		
	for (i = 0; i < 11; i++){
		a[i] = i;
    }

	myid = omp_get_thread_num();   //   получение номера нити
    printf("Consecutive part 1, myid = %d\n", myid);

	//printf("Consecutive part 1, S = %f \n", S);
	t_in = omp_get_wtime();
	printf("----------------------------\n");


#pragma omp parallel shared (S), private(num_threads, myid, s, i, j)
	{
		float part = 0;
		myid = omp_get_thread_num();
		num_threads = omp_get_num_threads();

		printf("Parallel part, myid = %d, amount of threads = %d\n", myid, num_threads);

//#pragma omp for wait
//		for (i = 0; i < 11; i++) {
//			a[i] = a[i] * 2;
//			printf("Thread %d has multiplied element %d, this elem now = %d \n", myid, i, a[i]);
//		}
		
		s = 0.0;

		t_in = omp_get_wtime();
#pragma omp for 
		for (i = 1; i <= N; i++){
			s = s + 1;
			integral = integral + 1;
		}
		t_out = omp_get_wtime();
		if (myid == 0) printf("!!! Time without critical is %f \n", t_out - t_in);

//#pragma omp atomic	
#pragma omp critical
		{
			S = S + s;
		}
		t_out = omp_get_wtime();
		if (myid == 0) printf("!!! Time WITH critical is %f \n", t_out - t_in);
			
		printf("Parallel part. I'm thread number %d, num_threads = %d, s = %f \n", myid, num_threads,s);


//#pragma omp for //collapse(2) //nowait
//		for (i = 1; i <= 10; i++) {
//			for (j = 1; j <= 1000000; j++) {
//				s++;
//			}
//		}
//		printf("I am thread %d, s = %f, mytime = %f \n", myid, s,  omp_get_wtime());
	}

	t_out = omp_get_wtime();
	printf("Consecutive part 2 integral with critical section, S = %f \n", S);
	printf("Consecutive part 2 integral without critical section, integral(S) = %f \n", integral);
	
	printf("Work time = %f \n", t_out - t_in);
	printf("----------------------------\n");
	
	myid = omp_get_thread_num();
    printf("Consecutive part 2 (after parallel section), myid = %d\n", myid);

	/*for (i = 0; i < 10; i++){
		printf("%d  ", a[i]);
	}*/
	printf("\n");
	return 0;

}
