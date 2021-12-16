#include <cstdlib>
#include <stdio.h>
#include <omp.h>
#include <chrono>

using namespace std::chrono;

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    double* a = new double[n];
    for (long int i = 0; i < n; i++) {
        a[i] = (double)rand() / RAND_MAX;
        // printf("a[%ld] = %f\n", i, a[i]);
    }    
    // printf("initial max value is %f\n", max_element);

    for (int num = 1; num <= 10; num++) {
        double max_value = a[0];
        auto start = high_resolution_clock::now();
        #pragma omp parallel for num_threads(num) reduction(max : max_value)
        for (int i = 0; i < n; i++) {
            max_value = max_value > a[i] ? max_value : a[i];
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        printf("Execution time with %d thread(s): %lld\n", num, duration.count());
        printf("max value is %f\n", max_value);
    }
    delete[] a;
    return 0;
}