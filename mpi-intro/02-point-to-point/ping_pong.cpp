#include <iostream>

#include <mpi.h>

using namespace std;

constexpr unsigned PING_PONG_LIMIT = 10;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    unsigned world_rank, world_size;

    MPI_Comm_rank(MPI_COMM_WORLD, reinterpret_cast<int*>(&world_rank));
    MPI_Comm_size(MPI_COMM_WORLD, reinterpret_cast<int*>(&world_size));

    unsigned ping_pong_count = 0;
    unsigned partner_rank = (world_rank + 1) % 2;
    while (ping_pong_count < PING_PONG_LIMIT)
    {
        if (world_rank == ping_pong_count % 2)
        {
            ping_pong_count++;
            MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            cout << world_rank << " sent and incremented ping_pong_count " << ping_pong_count << " to " << partner_rank << endl;
        } else
            {
            MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            cout << world_rank << " received ping_pong_count " << ping_pong_count <<" from " << partner_rank << endl;
        }
    }

    MPI_Finalize();

    return 0;
}
