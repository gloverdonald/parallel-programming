#include<mpi/mpi.h>

/*
 * > Scatter и Gather через Send и Recv
 * > На одном процессе есть массив из n чисел. Выводим его. При помощи
 * send, recv раздаем всем процессам по n/size чисел. Свою часть так же
 * копируем в другой массив  размера n/size.  Выводим номер каждого
 * процесса и его часть массива. Далее при помощи send, recv собираем все
 * части массива на каком-либо процессе в новый массив размера n.
 * Выводим его.
*/

int scatter(int *send_data, int sendcount, MPI_Datatype sendtype,
            int *recvbuf, int recvcount, MPI_Datatype recvtype,
            int root, MPI_Comm comm) {
    int rank;
    int size;
    MPI_Status status;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == root) {
        for (int i = 0; i < size; i++) {
            if (i != root)
                MPI_Send(&send_data[i * sendcount], sendcount, sendtype, i, 0, comm);
            else {
                for (int j = 0; j < recvcount; j++) {
                    recvbuf[j] = send_data[i * sendcount + j];
                }
            }
        }
    } else {
        MPI_Recv(&recvbuf[0], recvcount, recvtype, root, 0, comm, &status);
    }
    return 0;
}

int gather(int *sendbuf, int sendcount, MPI_Datatype sendtype,
           int *recvbuf, int recvcount, MPI_Datatype recvtype,
           int root, MPI_Comm comm) {
    int rank;
    int size;
    MPI_Status status;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == root) {
        for (int i = 0; i < size; i++) {
            if (i != root) {
                MPI_Recv(&recvbuf[i * recvcount], recvcount, recvtype, i, 0, comm, &status);
            } else {
                for (int j = 0; j < recvcount; j++) {
                    recvbuf[i * recvcount + j] = sendbuf[j];
                }
            }
        }
    } else {
        MPI_Send(&sendbuf[0], sendcount, sendtype, root, 0, comm);
    }
    return 0;
}

int main() {
    srand((int) time(nullptr));
    int N = 12;

    int rank, size;
    MPI_Init(nullptr, nullptr);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *a = new int[N];

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            a[i] = rand() % 100;
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    int *local_A = new int[N / size];
    int *b = new int[N];
    scatter(a, N / size, MPI_INT, local_A, N / size, MPI_INT, 0, MPI_COMM_WORLD);
    gather(local_A, N / size, MPI_INT, b, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int j = 0; j < N; j++) {
            printf("%d ", b[j]);
        }
        printf("\n");
    }


    MPI_Finalize();
    return 0;
}