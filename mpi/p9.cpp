#include<mpi/mpi.h>


/*
 * > Инвертировать массив
 * > Перевернуть массив. Работа процессов должна быть сбалансирована.
 *   Можно использовать как и Scatterv, Gatherv, так и  Send, Recv.
*/
using namespace std;

int main() {
    srand((int) time(nullptr));
    int N = 12;

    int rank, size;
    MPI_Init(nullptr, nullptr);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *a = new int[N];
    int *res = new int[N];
    if (rank == 0) {
        for (int i = 0; i < N; ++i) {
            a[i] = rand() & 100;
            printf("%d ", a[i]);
        }
    }
    int *cnts = new int[size];
    int *inds = new int[size];
    int *rev_inds = new int[size];

    int rest = N;
    int k = rest / size;
    cnts[0] = k;
    inds[0] = 0;
    rev_inds[0] = N - k;
    for (int i = 1; i < size; ++i) {
        rest -= k;
        k = rest / (size - i);
        cnts[i] = k;
        inds[i] = inds[i - 1] + cnts[i - 1];
        rev_inds[i] = rev_inds[i - 1] - cnts[i];
    }

    int cnt = cnts[rank];
    int *data_loc = new int[cnt];

    MPI_Scatterv(a, cnts, inds, MPI_INT, data_loc, cnt, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < cnt / 2; ++i) {
        int temp = data_loc[i];
        data_loc[i] = data_loc[cnt - i - 1];
        data_loc[cnt - i - 1] = temp;
    }

    MPI_Gatherv(data_loc, cnt, MPI_INT, res, cnts, rev_inds, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", res[i]);
        }

    }

    MPI_Finalize();
    return 0;
}