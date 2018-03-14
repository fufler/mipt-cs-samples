#include <iostream>
#include <cassert>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

constexpr int NUM_PROCS = 5;
constexpr int NUM_INTS = 10;

int main(int, char** argv)
{
    key_t key = ftok(argv[0], 1);
    assert(key > 0);

    int semid = semget(key, NUM_PROCS, IPC_CREAT | S_IRUSR | S_IWUSR);
    assert(semid > 0);

    struct sembuf add = {0, 1, 0};
    struct sembuf sub = {0, -1, 0};

    int fd[2];
    pipe(fd);

    semop(semid, &add, 1);

    int idx, pid;
    for (idx = 1; idx <= NUM_PROCS; idx++)
        if (!(pid = fork()))
        {
            sub.sem_num = idx-1; 
            add.sem_num = idx % NUM_PROCS; 
            break;
        }


    if (pid == 0)
        for(int i = 0; i < NUM_INTS; i++)
        {
            semop(semid, &sub, 1);
            write(fd[1], &idx, sizeof(idx));
            semop(semid, &add, 1);
        }

    if (pid > 0)
    {
        for (int i = 0; i < NUM_PROCS*NUM_INTS; i++)
        {
            read(fd[0], &idx, sizeof(idx));
            cout << idx << endl;
        }
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}
