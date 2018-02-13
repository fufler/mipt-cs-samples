#include <unistd.h>
#include <wait.h>

#include <iostream>

using namespace std;

int main()
{

    pid_t pid = fork();

    if (pid == 0)
    {
        cout << "Running /bin/true" << endl;
        execl("/bin/true", "/bin/true", nullptr);
        exit(1);
    }

    int wstatus;

    wait(&wstatus);

    cout << "Return code for /bin/true is " << WEXITSTATUS(wstatus) << endl;
    
    pid = fork();

    if (pid == 0)
    {
        cout << "Running /bin/false" << endl;
        execl("/bin/false", "/bin/false", nullptr);
        exit(0);
    }

    wait(&wstatus);

    cout << "Return code for /bin/false is " << WEXITSTATUS(wstatus) << endl;

    return 0;
}
