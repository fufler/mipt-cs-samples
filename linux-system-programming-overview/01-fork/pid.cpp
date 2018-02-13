#include <unistd.h>

#include <iostream>

using namespace std;

int main()
{
    cout << "My pid is " << getpid() << ", parent pid is " << getppid() << endl;

    return 0;
}
