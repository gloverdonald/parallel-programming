#include<mpi/mpi.h>

using namespace std;

/*
 * > Maxmin матрицы
 * > Найти седловую точку матрицы. Распределение данных через scatterv.
 * Каждый процесс получает какое-то количество строк матрицы. Находит
 * для каждой строки минимум и выбирает из  них максимальный. Далее из
 * локальных максимумов выбирает глобальный. Проверить совпадают ли
 * maxmin и minmax.

*/

int main() {
    srand((int) time(nullptr));

    int rank, size;

    MPI_Init(nullptr, nullptr);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a = 5, b = 5;
    int n = a * b;


    int maxmin = 0, minmax = 10000;

    int *matrix = new int[n];

    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            matrix[i] = i;
        }
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                printf("%d ", matrix[i * b + j]);
            }
            printf("\n");
        }
    }

    int *cnts = new int[size];
    int *inds = new int[size];

    int rest = a;
    int k = a / size;
    cnts[0] = b * k;
    inds[0] = 0;
    // printf("%d\n", k);
    for (int i = 1; i < size; i++) {
        rest -= k;
        //printf("%d\n", k);
        k = rest / (size - i);
        cnts[i] = b * k;
        inds[i] = inds[i - 1] + cnts[i - 1];
    }

    int cnt = cnts[rank];
    int *temp_matrix = new int[cnt];

    MPI_Scatterv(matrix, cnts, inds, MPI_INT, temp_matrix, cnt, MPI_INT, 0, MPI_COMM_WORLD);

    int maxmin_loc = 0;
    int minmax_loc = 10000;
    for (int i = 0; i < cnt / b; ++i) {
        int row_min = 10000;
        int row_max = 0;
        for (int j = 0; j < b; ++j) {
            row_max = max(row_max, temp_matrix[i * b + j]);
            row_min = min(row_min, temp_matrix[i * b + j]);
        }
        maxmin_loc = max(maxmin_loc, row_min);
        minmax_loc = min(minmax_loc, row_max);
    }

    MPI_Reduce(&maxmin_loc, &maxmin, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&minmax_loc, &minmax, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);


    /*for (int i = 0; i < cnts[rank] / b; i++) {
        int min = 10000;
        int max = 0;
        for (int j = 0; j < b; j++) {
            a = temp_matrix[i * b + j];
            if (a < min) {
                min = a;
            }
            if (a > max) {
                max = a;
            }
        }

        if (min > result[0]) {
            temp[0] = min;
        }

        if (max < result[1]) {
            temp[1] = max;
        }

    }*/



    if (rank == 0) {
        printf("maxMin = %d. minMax = %d\n", maxmin, minmax);
    }


    MPI_Finalize();
    return 0;
}