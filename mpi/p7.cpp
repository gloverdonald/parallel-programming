#include<mpi/mpi.h>
#include <cmath>

using namespace std;

/*
 * > Умножение матрицы на вектор при разделении данных по столбцам
 * > На одном процессе заполняется матрица и вектор. Каждый процесс
 * получает несколько столбцов матрицы и столько же элементов вектора.
 * Рассчитывает частичную сумму результирующего вектора.  ci = A i,j * b j
 * для  j-го столбца. Если столбцов несколько, то cj суммируются. Далее все
 * частичные суммы собираются в результат.
*/
int main() {
    srand((int) time(nullptr));
    const int A = 2, B = 3;
    int *matrix = new int[A * B], *transpose_matrix = new int[A * B], *vector = new int[B];
    int *row_sum_loc = new int[A];
    int rank, size;
    MPI_Init(nullptr, nullptr);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("matrix:\n");
        for (int i = 0; i < A; ++i) {
            for (int j = 0; j < B; ++j) {
                matrix[i * B + j] = rand() % 20 + 1;
                printf("%d ", matrix[i * B + j]);
                transpose_matrix[j * A + i] = matrix[i * B + j];
            }
            printf("\n");
        }
        printf("vector: \n");
        for (int i = 0; i < B; ++i) {
            vector[i] = rand() % 20 + 1;
            printf("%d ", vector[i]);
        }
        printf("\n");
    }

    int *cnts = new int[size];
    int *inds = new int[size];

    int *cnts_vec = new int[size];
    int *inds_vec = new int[size];

    int rest = B;
    int k = rest / size;
    cnts[0] = k * A;
    inds[0] = 0;
    cnts_vec[0] = k;
    inds_vec[0] = 0;

    for (int i = 1; i < size; ++i) {
        rest -= k;
        k = rest / (size - i);
        cnts[i] = k * A;
        inds[i] = inds[i - 1] + cnts[i - 1];
        cnts_vec[i] = k;
        inds_vec[i] = cnts_vec[i - 1] + inds_vec[i - 1];
    }
    int cnt = cnts[rank];
    int *col_loc = new int[cnt];
    int cnt_vec = cnts_vec[rank];
    int *vec_loc = new int[cnt_vec];
    MPI_Scatterv(vector, cnts_vec, inds_vec, MPI_INT, vec_loc, cnt_vec, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatterv(transpose_matrix, cnts, inds, MPI_INT, col_loc, cnt, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < cnt_vec; ++i) {
        //printf("%d) ", rank);
        for (int j = 0; j < A; ++j) {
            //printf("%d * %d | ", vec_loc[i], col_loc[i * A + j]);
            row_sum_loc[j] += vec_loc[i] * col_loc[i * A + j];
        }
        // printf("\n");
    }
    int *row_sum = new int[A];
    MPI_Reduce(row_sum_loc, row_sum, A, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("ans: \n");
        for (int i = 0; i < A; ++i) {
            printf("%d ", row_sum[i]);
        }
    }

    MPI_Finalize();
}
