#include <unistd.h>
#include <fcntl.h>


#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>

using namespace std;

constexpr int BUF_SIZE = 1000;

int main()
{
    int fd = open("/proc/uptime", O_RDONLY);

    char buf[BUF_SIZE+1];

    int sz = read(fd, buf, BUF_SIZE);
    buf[sz] = 0;

    close(fd);

    char* pos = strchr(buf, ' ');
    assert(pos);

    *pos = 0;

    float uptime = atof(buf) / 3600;

    cout << "Uptime is " << fixed << setprecision(1) << uptime << " hours" << endl;

    return 0;
}
