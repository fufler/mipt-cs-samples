#include <iostream>
#include <cassert>
#include <cstring>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>

using namespace std;

constexpr int MEM_SIZE = 100;
constexpr int READ = 1;
constexpr int WRITE = 2;

int main(int argc, char **argv)
{
    assert(argc == 2);

    key_t key = ftok(argv[0], 1);
    assert(key != -1);

    int memid;
    int action;
    
    if (!strcmp(argv[1], "write"))
    {
        memid = shmget(key, MEM_SIZE, IPC_CREAT | S_IRUSR | S_IWUSR);
        assert(memid != -1);

        action = WRITE;
    } else if (!strcmp(argv[1], "read"))
    {
        memid = shmget(key, MEM_SIZE, 0);
        if (memid == -1)
        {
            cerr << "Memory segment does not exist" << endl;
            return -1;
        }

        action = READ;
    } else
    {
        cerr << "Unknown operation: " << argv[1] << endl;
        return -2;
    }

    auto ptr = static_cast<char*>(shmat(memid, nullptr, 0));
    assert(reinterpret_cast<long>(ptr) > 0);

    if (action == READ)
        cout << "Memory content is: " << ptr << endl;
    else
        strcpy(ptr, "Hello, shared memory world!");
}
