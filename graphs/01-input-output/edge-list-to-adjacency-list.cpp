#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
    map<string, int> name_to_number;
    vector<string> names;

    int e, v;

    cin >> v >> e;

    int** graph = new int*[v];

    for (int i = 0; i < v; i++) {
        graph[i] = new int[v]();
    }

    for (int i = 0; i < e; i++) {
        string from, to;

        cin >> from >> to;

        if (name_to_number.count(from) == 0) {
           name_to_number[from] = names.size();
           names.push_back(from);
        }

        if (name_to_number.count(to) == 0) {
           name_to_number[to] = names.size();
           names.push_back(to);
        }

        graph[name_to_number[from]][name_to_number[to]] = 1;
    }

    name_to_number.clear();

    for (int i = 0; i < v; i++) {
        cout << names[i] << ": ";
        for (int j = 0; j < v; j++)
            if (graph[i][j] == 1)
                cout << names[j] << " ";
        cout << endl;
    }

    for (int i = 0; i < v; i++)
        delete[] graph[i];
    delete[] graph;


    return 0;
}
