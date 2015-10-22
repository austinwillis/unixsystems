//CS375 Homework 1
//Austin Willis
//build with make testmytrig

#include <cmath>
#include "mytrig.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;
int main() {
  cout << "Trig Function Tests      mytrig    cmath" << endl;
  for (unsigned int i = 0; i <= 180; i += 10) {
	cout << "Sin " << setfill('0') << setw(3)
	<< i << " = " << "           ";
	printf("%*f  |  %*f", 8, mysin((M_PI*i)/180), 8, sin((M_PI*i)/180));
	cout << endl;
  }
  for (unsigned int i = 0; i <= 180; i += 10) {
	cout << "Cos " << setfill('0') << setw(3)
	<< i << " = " << "           ";
	printf("%*f  |  %*f", 8, mycos((M_PI*i)/180), 8, cos((M_PI*i)/180));
	cout << endl;
  }
  for (unsigned int i = 0; i <= 180; i += 10) {
	cout << "Tan " << setfill('0') << setw(3)
	<< i << " = " << "           ";
	printf("%*f  |  %*f", 8,  mytan((M_PI*i)/180), 8, tan((M_PI*i)/180));
	cout << endl;
  }
  return 0;
}
