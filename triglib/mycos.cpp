//CS375 Homework 1
//Austin Willis

#include <cmath> // abs()
#include "mytrig.h"
using namespace std;
double mycos(double angle)
{
  return mysin(angle + (M_PI / 2));
}
