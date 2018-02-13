#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    cout << "Number of arguments: " << argc << endl;
    cout << "Arguments:" << endl;

    for (int i = 0; i < argc; i++)
        cout << argv[i] << endl;

    return 0;
}
