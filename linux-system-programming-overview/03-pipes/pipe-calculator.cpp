#include <unistd.h>

#include <iostream>

using namespace std;

int main()
{
    int fd[4];

    pipe(fd);
    pipe(fd+2);

    if (fork() > 0)
    {
        close(fd[0]);
        close(fd[3]);

        int ints[2] = {14, 3};
        
        cout << ints[0] << "*" << ints[1] << "=";

        write(fd[1], ints, sizeof(ints[0])*2);
        read(fd[2], ints, sizeof(ints[0]));

        cout << ints[0] << endl;
        
        close(fd[1]);
        close(fd[2]);
    }
    else
    {
        close(fd[1]);
        close(fd[2]);

        int a, b;
        
        read(fd[0], &a, sizeof(a));
        read(fd[0], &b, sizeof(b));

        a *= b;

        write(fd[3], &a, sizeof(a));

        close(fd[0]);
        close(fd[3]);
    }

    return 0;
}
