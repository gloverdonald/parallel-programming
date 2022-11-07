#include<mpi/mpi.h>

using namespace std;

/*
 * > Hello world из всех процессов (2 балла)
 * > уметь запускать MPI
*/

int main() {
    int size, rank;

    MPI_Init(nullptr, nullptr);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Hello World! from process %d out of %d\n", rank, size);

    MPI_Finalize();
    return 0;
}