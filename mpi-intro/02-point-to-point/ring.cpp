#include <iostream>

#include <mpi.h>

using namespace std;

constexpr unsigned PING_PONG_LIMIT = 10;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    unsigned world_rank, world_size;

    MPI_Comm_rank(MPI_COMM_WORLD, reinterpret_cast<int*>(&world_rank));
    MPI_Comm_size(MPI_COMM_WORLD, reinterpret_cast<int*>(&world_size));

    int token;
    if (world_rank != 0)
    {
        unsigned source = world_rank - 1;
        MPI_Recv(&token, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        cout << "Process " << world_rank << " received token " << token << " from process " << source << endl;
        token++;
    } else
        token = -1;

    MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        unsigned source = world_size - 1;
        MPI_Recv(&token, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        cout << "Process 0 received token " << token << " from process " << source << endl;
    }

    MPI_Finalize();

    return 0;
}
