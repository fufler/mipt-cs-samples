#include <cstring>

#include <iostream>

using namespace std;

int main(int argc, char** argv, char** envp)
{
    int max_len = 0;
    char* longest_var_name;

    while (*envp)
    {
        char* pos = strchr(*envp, '=');
        if (pos)
        {
            int len = pos - *envp;
            if (len > max_len)
            {
                max_len = len;
                longest_var_name = *envp;
            }
        }

        envp++;
    }

    char* var_name = new char[max_len+1];
    strncpy(var_name, longest_var_name, max_len);

    cout << var_name << endl;

    delete[] var_name;

    return 0;
}
