#include <unistd.h>
#include <fcntl.h>

#include <cassert>

using namespace std;

constexpr int BUF_SIZE = 1000;

int main(int argc, char** argv)
{
    assert(argc == 3);

    int rfd = open(argv[1], O_RDONLY);
    int wfd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    char buf[BUF_SIZE];
    int sz;

    while ((sz = read(rfd, buf, BUF_SIZE)) > 0)
        write(wfd, buf, sz);

    close(rfd);
    close(wfd);
}
