#include <unistd.h>
#include <sys/wait.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono_literals;

static const int NUM_FORKS = 3;

int main()
{

    int i;
    
    vector<pid_t> child_pids;
    child_pids.reserve(NUM_FORKS);

    pid_t pid;

    for (i = 0; i < NUM_FORKS; i++)
    {
        cout << "Parent process: forking #" << i << endl;

        pid = fork();

        if (pid == 0)
            break;

        child_pids.push_back(pid);
    }

    if (pid == 0)
    {
        cout << "Child process with pid " << getpid() << " and child_pids size " << child_pids.size() << ": sleeping" << endl;
        this_thread::sleep_for(2s);
        cout << "Child process: terminating with code " << i << endl;
        exit(i);
    }

    for (i = 0; i < NUM_FORKS; i++)
    {
        cout << "Parent process: waiting for child process with pid " << pid << endl;
        int wstatus;
        waitpid(child_pids[i], &wstatus, 0);
        cout << "Child process with pid " << child_pids[i] << " terminated with exit code " << WEXITSTATUS(wstatus) << endl;
    }

    return 0;
}
