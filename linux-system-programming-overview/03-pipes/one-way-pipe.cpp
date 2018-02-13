#include <unistd.h>

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    char* buf;
    int fd[2];

    pipe(fd);

    pid_t pid = fork();

    if (pid > 0)
    {
        close(fd[0]);

        buf = new char[100];
        strcpy(buf, "Hello, world!");

        write(fd[1], buf, strlen(buf));
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        buf = new char[50];

        int nb = read(fd[0], buf, 30);
        close(fd[0]);

        cout << "Got message (length=" << nb << ") from parent: " << buf << endl;
    }

    return 0;
}
