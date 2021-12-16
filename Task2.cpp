#include <cstdlib>
#include <stdio.h>
#include <omp.h>
#include <chrono>

using namespace std::chrono;

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    double* a = new double[n];
    for (long int i = 0; i < n; i++) { //generate the vector of numbers from 0 to 1
        a[i] = (double)rand() / RAND_MAX;
        // printf("a[%ld] = %f\n", i, a[i]);
    }    

    for (int num = 1; num <= 10; num++) { //the number of threads
        double max_value = a[0]; //first value of vector is the initial value of max_value variable at the beginning of each iteration
        auto start = high_resolution_clock::now(); //start the time count
        #pragma omp parallel for num_threads(num) reduction(max : max_value) //specifying the omp parameters that we need: "for" for parallel usage of for loop,
        //num_threads for specifying the number of threads and reduction for defining the operation and private variable max_value to each thread
        for (int i = 0; i < n; i++) {
            max_value = max_value > a[i] ? max_value : a[i];
        }
        auto stop = high_resolution_clock::now(); //stop the time count
        auto duration = duration_cast<microseconds>(stop - start); //count the difference of start and stop
        printf("Execution time with %d thread(s): %lld\n", num, duration.count());
        printf("max value is %f\n", max_value);
    }
    delete[] a;
    return 0;
}