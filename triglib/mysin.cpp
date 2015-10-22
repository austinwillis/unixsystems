//CS375 Homework 1
//Austin Willis
#include <cmath> // abs()
#include "mytrig.h"
using namespace std;
static double utility(double y)
{ return 3.0 * y - 4.0 * y * y * y; }
double mysin(double angle)
{
 if (abs(angle) <= 0.1)
 return angle;
 else
 return utility(mysin(angle/3.0));
}
