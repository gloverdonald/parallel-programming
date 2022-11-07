#include <iostream>
#include <omp.h>

int main() {
#pragma omp parallel default(none) num_threads(400)
    {
        int rank, size;
        rank = omp_get_thread_num();
        size = omp_get_num_threads();
        for (int i = size - 1; i >= 0; i--) {
#pragma omp barrier
            {
                if (i == omp_get_thread_num()) {
                    printf("hello world: %d of %d\n", rank, size);
                }
            }
        }
    }
    return 0;
}
