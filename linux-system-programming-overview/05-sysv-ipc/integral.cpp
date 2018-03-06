#include <iostream>
#include <cassert>
#include <cstring>
#include <cmath>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

double f(double x)
{
    return sin(x);
}

constexpr double A = 0.0;
constexpr double B = M_PI;

int main(int argc, char **argv)
{
    assert(argc == 2);

    key_t key = ftok(argv[0], 1);
    assert(key != -1);

    int num_procs = atoi(argv[1]);

    int memid = shmget(key, sizeof(double)*num_procs, IPC_CREAT | S_IRUSR | S_IWUSR);
    assert(memid != -1);

    auto ptr = static_cast<double*>(shmat(memid, nullptr, 0));
    assert(reinterpret_cast<long>(ptr) > 0);

    double dx = (B-A)/num_procs;

    int proc_index;
    int pid = 0;
    for (proc_index = 0; proc_index < num_procs; proc_index++)
        if (!(pid = fork()))
            break;

    if (pid == 0)
        ptr[proc_index] = dx*(f(A+dx*proc_index) + f(A+dx*(1+proc_index)))/2;
    else
    {
        for (int i = 0; i < num_procs; i++)
            wait(nullptr);

        double res = 0.0;

        for (int i = 0; i < num_procs; i++)
            res += ptr[i];

        cout << res << endl;

        shmctl(memid, IPC_RMID, nullptr);
    }
}
