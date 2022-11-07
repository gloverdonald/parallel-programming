#include<mpi/mpi.h>


/*
 * > Время передачи для разных Send-oв (6 баллов)
 * > Программу тестируем на двух процессах. Используем Send, Ssend, Bsend
 *   и Rsend  - передаем какой-либо длинный массив или строку второму
 *   процессу, и получаем  обратно. Замеряем время потраченные на эти
 *   операции.
.
*/
using namespace std;

int main() {
    srand((int) time(nullptr));
    int N = 100000;

    int size, rank;
    MPI_Status status;

    MPI_Init(nullptr, nullptr);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int x[N];
    double start, end, total;

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            x[i] = rand() % 100;
        }
    }

    //Send
    if (rank == 0) {
        start = MPI_Wtime();
        MPI_Send(x, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(x, N, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }


    if (rank == 0) {
        end = MPI_Wtime();
        total = end - start;

        printf("Send  %.6f\n", total);
    }

    //Ssend
    if (rank == 0) {
        start = MPI_Wtime();
        MPI_Ssend(x, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(x, N, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }


    if (rank == 0) {
        end = MPI_Wtime();
        total = end - start;

        printf("Ssend  %.6f\n", total);
    }

    //Rsend
    if (rank == 0) {
        start = MPI_Wtime();

        MPI_Rsend(x, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(x, N, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }


    if (rank == 0) {
        end = MPI_Wtime();
        total = end - start;

        printf("Rsend  %.6f\n", total);
    }

    //Bsend
    MPI_Buffer_attach(malloc(N * sizeof(int)), N * sizeof(int) + MPI_BSEND_OVERHEAD);

    if (rank == 0) {
        start = MPI_Wtime();
        MPI_Bsend(x, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(x, N, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }


    if (rank == 0) {
        end = MPI_Wtime();
        total = end - start;

        printf("Bsend  %.6f\n", total);
    }

    MPI_Finalize();
    return 0;
}