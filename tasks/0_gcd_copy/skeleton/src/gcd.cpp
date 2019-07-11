#include "lib/gcd.hpp"

int gcd(int x, int y)
{
    if (x > 0 && y > 0)
    {
        while (x != y)
        {
            if (x > y)
            {
                x = x - y;
            }
            else
            {
                y = y - x;
            }
        }
        return x;
    }
    return -1;
}
