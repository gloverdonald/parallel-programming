#include<mpi/mpi.h>

using namespace std;

/*
 * > Скалярное произведение векторов
 * > Распределение данных через scatterv. Есть два массива – надо найти суммы произведений соответствующих координат.
 */

int main() {
    srand((int) time(nullptr));

    const int N = 10;
    int rank, size, a[N], b[N], sum = 0;

    MPI_Init(nullptr, nullptr);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            a[i] = rand() % 3;
            b[i] = rand() % 3;
            printf("%d: a=%d, b=%d\n", i, a[i], b[i]);
        }
    }
    int *cnts = new int[size];
    int *inds = new int[size];

    int rest = N;
    int k = N / size;
    cnts[0] = k;
    inds[0] = 0;

    for (int i = 1; i < size; i++) {
        rest -= k;
        k = rest / (size - i);
        cnts[i] = k;
        inds[i] = inds[i - 1] + cnts[i - 1];
    }

    int cnt = cnts[rank];
    int *a_loc = new int[cnt];
    int *b_loc = new int[cnt];

    MPI_Scatterv(a, cnts, inds, MPI_INT, a_loc, cnt, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatterv(b, cnts, inds, MPI_INT, b_loc, cnt, MPI_INT, 0, MPI_COMM_WORLD);

    int sum_loc = 0;

    for (int i = 0; i < cnt; i++) {
        sum_loc += a_loc[i] * b_loc[i];
    }

    MPI_Reduce(&sum_loc, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("%.d\n", sum);
    }
    MPI_Finalize();
    return 0;
}