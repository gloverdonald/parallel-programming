#include <mpi/mpi.h>
#include <iostream>
#include <vector>

using namespace std;

/*
 * > Maксимум массива
 * > уметь использовать что-то из send, recv,  bcast, reduce
*/

int main() {
    //srand((int) time(0));

    const int N = 40;
    int rank, size;
    int x[N], public_max = 0, local_max = 0;

    MPI_Init(nullptr, nullptr);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            x[i] = rand() % 100 + 1;
        }
    }

    MPI_Bcast(x, N, MPI_INT, 0, MPI_COMM_WORLD);


    int k = N / size;
    int i1 = k * rank;
    int i2 = k * (rank + 1);

    if (rank == size - 1) {
        i2 = N;
    }

    for (int i = i1; i < i2; i++) {
        local_max = max(local_max, x[i]);
    }
    printf("proc - %d, max = %d\n", rank, local_max);

    MPI_Reduce(&local_max, &public_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("max = %.2d\n", public_max);
    }

    MPI_Finalize();
    return 0;
}