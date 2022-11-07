#include <iostream>
#include <omp.h>
#include <csignal>


int main() {
    int threads_count = 100;
    omp_set_num_threads(threads_count);
    int maxt = threads_count;
#pragma omp parallel default(none) shared(maxt)
    {
        while (omp_get_thread_num() != maxt - 1) { ;
        }
#pragma omp critical
        {
            printf("hello world: %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
            maxt--;
        }
    }
    return 0;
}
