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
        close(fd[0]);

        dup2(fd[1], 1);

        cout << "Hello!";

    }
    else
    {
        close(fd[1]);

        dup2(fd[0], 0);

        string s;
        cin >> s;

        cout << "Got message from parent: " << s << endl;
    }

    return 0;
}
