#include <iostream>

using namespace std;

struct test
{
    long l;
    char c;
    float x, y;
};

int main()
{
    test t;

    cout << "Struct size: " << sizeof(t) << endl;
    cout << "l size: " << sizeof(t.l) << ", l offset: " << (char*)&t.l - (char*)&t << endl;
    cout << "c size: " << sizeof(t.c) << ", c offset: " << (char*)&t.c - (char*)&t << endl;
    cout << "x size: " << sizeof(t.x) << ", x offset: " << (char*)&t.x - (char*)&t << endl;
    cout << "y size: " << sizeof(t.y) << ", y offset: " << (char*)&t.y - (char*)&t << endl;

    return 0;
}
