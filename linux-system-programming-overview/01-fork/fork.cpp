#include <unistd.h>

#include <iostream>

using namespace std;

int main()
{
    pid_t pid = fork();

    switch (pid)
    {
        case -1: cerr << "Failed to call fork()" << endl; exit(-1);
        case  0: cout << "I'm child process with pid " << getpid() << ",parent pid is " << getppid() << endl; break;
        default: cout << "I'm parent process with pid " << getpid() << ", child pid is " << pid << endl; break;
    }

    return 0;
}
