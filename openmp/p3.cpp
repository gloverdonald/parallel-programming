#include <iostream>
#include <omp.h>

int main() {
    int a = 11, b = 12;
    printf("1)a:=%d, b:=%d\n", a, b);
#pragma omp parallel num_threads(2) default(none) private(a) firstprivate(b)
    {
        a += omp_get_thread_num();
        b += omp_get_thread_num();
        printf("omp_get_thread_num():=%d, a:=%d, b:=%d\n", omp_get_thread_num(), a, b);
    }
    printf("2)a:=%d, b:=%d\n", a, b);

#pragma omp parallel num_threads(4) default(none) shared(a) private(b)
    {
        a -= omp_get_thread_num();
        b -= omp_get_thread_num();
        printf("omp_get_thread_num() := %d, a := %d, b := %d\n", omp_get_thread_num(), a, b);
    }
    printf("3)a:=%d, b:=%d", a, b);
    return 0;
}