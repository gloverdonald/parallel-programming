#include <iostream>
#include <omp.h>

int main() {

#pragma omp parallel default(none) num_threads(8)
    {
        int rank, size;
        rank = omp_get_thread_num();
        size = omp_get_num_threads();
        printf("hello world: %d of %d\n", rank, size);
    }
    return 0;
}
