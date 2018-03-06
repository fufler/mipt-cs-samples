#include <unistd.h>
#include <fcntl.h>

#include <cassert>

using namespace std;

constexpr int BUF_SIZE = 1000;

int main(int argc, char** argv)
{
    assert(argc == 3);

    int pfd[2];
    int fd;

    char buf[BUF_SIZE];
    int sz;


    pipe(pfd);

    if (!fork())
    {
        close(pfd[0]);

        fd = open(argv[1], O_RDONLY);

        while ((sz = read(fd, buf, BUF_SIZE)) > 0)
            write(pfd[1], buf, sz);

        close(pfd[1]);
    }
    else
    {
        close(pfd[1]);

        fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

        while ((sz = read(pfd[0], buf, BUF_SIZE)) > 0)
            write(fd, buf, sz);

        close(pfd[0]);
    }

    close(fd);
}
