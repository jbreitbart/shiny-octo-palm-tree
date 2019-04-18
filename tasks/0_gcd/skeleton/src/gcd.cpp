#include "lib/gcd.hpp"
#include "math.h"

int gcd(int a, int b)
{
    int h;
    if (a == 0)
        return abs(b);
    if (b == 0)
        return abs(a);

    do
    {
        h = a % b;
        a = b;
        b = h;
    } while (b != 0);

    return abs(a);
}
