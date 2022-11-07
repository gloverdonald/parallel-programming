#include<mpi/mpi.h>

int main() {
    int number = 100;
    MPI_Init(nullptr, nullptr);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *send = new int[1];
    int *recv = new int[1];

    int to = rank + 1;
    int from = rank - 1;

    if (rank == 0) {
        from = size - 1;
    }

    if (rank == size - 1) {
        to = 0;
    }

    // 0 процесс отправляет следующему процессу число
    if (rank == 0) {
        send[0] = number;
        MPI_Send(send, 1, MPI_INT, to, to, MPI_COMM_WORLD);
        printf("Send from %d to %d: %d\n", rank, to, send[0]);
    }
    if (rank != 0) {
        MPI_Recv(recv, 1, MPI_INT, from, rank, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        printf("Receive from %d to %d: %d\n", from, rank, recv[0]);
        send[0] = recv[0] + 1;

        MPI_Send(send, 1, MPI_INT, to, to, MPI_COMM_WORLD);
        printf("Send from %d to %d: %d\n", rank, to, send[0]);
    }

    if (rank == 0) {
        MPI_Recv(recv, 1, MPI_INT, from, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        printf("Receive from %d to %d\nResult: %d\n", from, rank, recv[0]);
    }

    MPI_Finalize();
}