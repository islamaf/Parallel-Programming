#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double myFunc(double x){
    double y = 4/(1+x*x);
    return y;
}

int main(){
    int N = 10;
    double a = 0.0;
    double b = 1.0;
    double iterated_area = 0.0;

    // time variables
    double start, end, total;

    double integral;
    double iterated_integral = 10.0;
    double h = (b-a)/N;
    double my_result = (myFunc(a) + myFunc(b))/2.0;

    start = omp_get_wtime();
    omp_set_num_threads(3);
    //firstprivate
    #pragma omp parallel private(integral, iterated_integral) shared(iterated_area)
    {
        //printf("Iterated integral = %f\n", iterated_integral);
        #pragma omp for
        for(int i = 1; i <= N-1; i++){
            integral = a + i*h;
            iterated_integral += myFunc(integral);
        }

        #pragma omp critical
            iterated_area += iterated_integral;
    }

    iterated_area = (iterated_area + my_result) * h;

    end = omp_get_wtime();
    total = end - start;

    printf("Area = %lf\n", iterated_area);
    printf("Time = %.5f\n", total);

    return 0;
}
