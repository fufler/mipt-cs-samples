#include <unistd.h>

#include <iostream>

using namespace std;

int main()
{
    int fd[2];

    pipe(fd);

    pid_t pid = fork();

    if (pid > 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);

        cerr << "Output from child process:" << endl;
        
        string s;
        while (cin)
        {
            getline(cin, s);
            cerr << s << endl;
        }

        close(fd[0]);


    }
    else
    {
        close(fd[0]);

        dup2(fd[1], STDOUT_FILENO);

        execl("/usr/bin/free", "/usr/bin/free", "-g", nullptr);
    }

    return 0;
}
