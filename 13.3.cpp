#include <iostream>
#include <omp.h>
#include <csignal>

int main() {
    omp_set_num_threads(20);
    int thread_id, i;
#pragma omp parallel private(thread_id) default(none)
    {
        thread_id = omp_get_thread_num();
#pragma omp for private(i) ordered
        for (i = 0; i < omp_get_num_threads(); i++)
#pragma omp ordered
                printf("hello world: %d of %d\n", omp_get_num_threads() - thread_id, omp_get_num_threads() - i);
    }
    return 0;
}
