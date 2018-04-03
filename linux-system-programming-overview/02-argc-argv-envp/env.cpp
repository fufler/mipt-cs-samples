#include <iostream>

using namespace std;

int main(int, char**, char** envp)
{
    cout << endl << "Environment variables:" << endl;
    for (; *envp; cout << *(envp++) << endl);


    return 0;
}
