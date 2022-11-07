#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    omp_set_num_threads(3);
#pragma omp parallel default(none) if(omp_get_max_threads() > 2)
    {
        printf("First section: %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    omp_set_num_threads(2);
#pragma omp parallel default(none) if(omp_get_max_threads() > 2)
    {
        printf("Section section: %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }
    return 0;
}
