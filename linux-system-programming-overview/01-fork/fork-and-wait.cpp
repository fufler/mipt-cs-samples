#include <unistd.h>
#include <sys/wait.h>

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono_literals;


int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        cout << "Child process: sleeping" << endl;
        this_thread::sleep_for(10s);
        cout << "Child process: terminating" << endl;
    }
    else
    {
        cout << "Parent process: waiting for child process with pid " << pid << endl;
        int wstatus;
        waitpid(pid, &wstatus, 0);
        cout << "Child process terminated with exit code " << WEXITSTATUS(wstatus) << endl;
    }

    return 0;
}
