#include "angteRotation.h"
#include "stdio.h"

float second(int s)
{
    return  6*s;

}

float minute(int m)
{
    return 6 * m;
}

float hour(int h)
{
    float res = 30 * (h%12);
    printf("Hour:%d\nAngle:%f\n", h, res);
    return res;
}