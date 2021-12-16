#include <cstdlib>
#include <omp.h>
#include <stdio.h>
#include <chrono>
#include <iostream>

using namespace std::chrono;

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int** a = new int*[n];
    int** b = new int*[n];
    long** c = new long*[n];
    for(int i = 0; i < n; ++i) {
        a[i] = new int[m];
        b[i] = new int[m];
        c[i] = new long[m];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = rand() % 1000 + 1;
            b[i][j] = rand() % 1000 + 1;
        }
    }
    printf("Loop order: k-j-i\n");
    for (int num = 1; num <= 10; num++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                c[i][j] = 0;
            }
        }
        auto start = high_resolution_clock::now();
        #pragma omp parallel for num_threads(num)
            for (int k = 0; k < m; k++) {
                for (int j = 0; j < m; j++) {
                    for (int i = 0; i < n; i++){
                        c[i][j] = c[i][j] + a[i][k] * b[k][j];
                    }
                }
            }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        printf("Execution time with %d thread(s): %lld\n", num, duration.count());
    }
    // std::cout << "-------------Matrix A-------------" << std::endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         std::cout << a[i][j] << ' ';
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << "-------------Matrix B-------------" << std::endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         std::cout << b[i][j] << ' ';
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << "-------------Matrix C-------------" << std::endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         std::cout << c[i][j] << ' ';
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}