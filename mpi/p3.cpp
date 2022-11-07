#include<mpi/mpi.h>
#include <iostream>

using namespace std;
/*
 * > Вычисление числа Пи методом Монте-Карло (3 баллов)
 * > метод Монте-Карло для получения Пи, понимается как
 * генерирование случайной последовательности точек
 * из квадрата со сторонами 2 и центром в центре координат.
 * Доля точек попавших в круг с радиусом один умноженная на 4
 * должна стремиться к числу Пи. Распараллеливание заключается
 * в сбалансированном распределении итераций по процессам.
*/
int main() {
    srand((int) time(0));

    int rank, size;

    long sum = 0;

    MPI_Init(nullptr, nullptr);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const long N = 10e8;
    long in = 0;

    long k = N / size;
    long i1 = k * rank;
    long i2 = k * (rank + 1);

    if (rank == size - 1) {
        i2 = N;
    }

    for (long i = i1; i < i2; i++) {
        long x, y;
        x = rand();
        y = rand();
        if (x * x + y * y <= (long) RAND_MAX * RAND_MAX) {
            in++;
        }
    }

    MPI_Reduce(&in, &sum, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("PI = %f\n", (double) sum / N * 4);
    }


    /*if (rank == 0) {
        long sum = in;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&in, 1, MPI_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, nullptr);
            sum += in;
        }
        printf("PI = %f\n", (double) sum / N * 4);
    } else {
        MPI_Send(&in, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
    }*/
    MPI_Finalize();
    return 0;
}