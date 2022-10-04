#include <iostream>
#include <omp.h>
#include <csignal>

int main() {
    omp_set_num_threads(8);
#pragma omp parallel for schedule(static, 1) default(none)
    for (int i = 0; i < omp_get_num_threads(); i++) {
        sleep(omp_get_num_threads() - i);
        printf("hello world: %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }
    return 0;
}
