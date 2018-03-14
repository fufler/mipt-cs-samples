#include <iostream>
#include <cassert>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main(int, char** argv)
{
    key_t key = ftok(argv[0], 1);
    assert(key > 0);

    int semid = semget(key, 1, IPC_CREAT | S_IRUSR | S_IWUSR);
    assert(semid > 0);

    struct sembuf lock = {0, -1, 0};
    struct sembuf unlock = {0, 1, 0};

    int fd[2];
    pipe(fd);

    semop(semid, &unlock, 1);

    int idx, pid;
    for (idx = 0; idx < 2; idx++)
        if (!(pid = fork()))
            break;


    if (pid == 0)
        for(int i = 0; i < 100; i++)
        {
            semop(semid, &lock, 1);
            write(fd[1], &idx, sizeof(idx));
            semop(semid, &unlock, 1);
        }

    if (pid > 0)
    {
        for (int i = 0; i < 2*100; i++)
        {
            read(fd[0], &idx, sizeof(idx));
            cout << idx << endl;
        }
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}
