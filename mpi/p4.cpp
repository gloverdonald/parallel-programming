#include<mpi/mpi.h>

using namespace std;

/*
 * > Среднее арифметическое среди положительных чисел массива
 * > Распределение данных через scatterv.
 *   При сборе данных использовать одну операцию но с двумя числами.
*/

int main(int argc, char **argv) {
    srand((int) time(0));
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a[2] = {0, 0};
    int b[2] = {0, 0};

    const int N = 10;
    int data[N];

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            data[i] = rand() % 100 - 50;
            printf("%d ", data[i]);
            printf("\n");
        }
    }

    int rest = N;
    int *cnts = new int[size];
    int *inds = new int[size];
    int k = N / size;

    cnts[0] = k;
    inds[0] = 0;
    for (int i = 1; i < size; ++i) {
        rest -= k;
        k = rest / (size - i);
        cnts[i] = k;
        inds[i] = inds[i - 1] + cnts[i - 1];
    }


    int cnt = cnts[rank];
    int *data_loc = new int[cnt];

    MPI_Scatterv(data, cnts, inds, MPI_INT, data_loc, cnt, MPI_INT,
                 0, MPI_COMM_WORLD);

    for (int i = 0; i < cnt; ++i) {
        if (data_loc[i] > 0) {
            a[0] += data_loc[i];
            a[1]++;
        }
    }


    MPI_Reduce(&a, &b, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("avg := %f\n", (double) b[0] / b[1]);
    }

    MPI_Finalize();
    return 0;
}