#include <cstring>
#include <cassert>

#include <iostream>

using namespace std;

int main(int argc, char** argv, char** envp)
{
    assert(argc == 2);

    int l = strlen(argv[1])+1;
    char* substring = new char[l+1];

    strcpy(substring, argv[1]);
    substring[l-1] = '=';
    substring[l] = 0;

    for (; *envp && strncmp(*envp, substring, l); envp++);

    if (*envp)
        cout << *envp + l << endl;

    return 0;
}
