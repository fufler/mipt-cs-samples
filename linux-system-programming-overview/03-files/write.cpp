#include <unistd.h>
#include <fcntl.h>

#include <cstring>
#include <cstdio>

constexpr int BUF_SIZE = 1000;

using namespace std;

int main(int argc, char** argv)
{
    int fd = open("/tmp/hello_world", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    char buf[BUF_SIZE];

    sprintf(buf, "Hello from %s program! My arguments:\n", argv[0]);

    write(fd, buf, strlen(buf));

    for (int i = 1; i < argc; i++)
    {
        write(fd, argv[i], strlen(argv[i]));
        write(fd, "\n", 1);
    }

    close(fd);

    return 0;
}
