#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    uint8_t a = 4;
    uint8_t b = 10;
    uint16_t c = 2;

    uint16_t d1 = a*b + c;
    uint16_t d2 = 0;

    cout << "d1 == " << d1 << ", d2 == " << d2 << endl;

      __asm
    (
          "movb %1, %%al\n"
          "movb %2, %%bl\n"
          "mul %%bl\n"

          "movw %3, %%bx\n"
          "add %%bx, %%ax\n"

          "movw %%ax, %0\n"

        :"=r"(d2)
        :"r"(a), "r" (b), "r"(c)
    );

    cout << "d1 == " << d1 << ", d2 == " << d2 << endl;


    return 0;
}
