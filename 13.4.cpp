#include <iostream>
#include <omp.h>
#include <csignal>

void rec(int i) {
    if (i == -1) {
        return;
    }
#pragma omp parallel default(none) shared(i)
    {
        if (i == omp_get_thread_num()) {
            printf("hello world: %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }
    rec(i - 1);
}

int main() {
    int threads_count = 100;
    omp_set_num_threads(threads_count);
    rec(threads_count);
    return 0;
}
