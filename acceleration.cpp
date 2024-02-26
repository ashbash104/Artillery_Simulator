/***********************************************************************
 * Source File:
 *    Acceleration
 * Author:
 *    Ashlee Hart
 ************************************************************************/
using namespace std;
#include <iostream>
#include "acceleration.h"
/******************************
*ACCELERATION CONSTRUCTOR
*******************************/
Acceleration::Acceleration(double a, Angle angle)
{
   setDDX(computeDDX(a, angle));
   setDDY(computeDDY(a, angle));
}
/**********************************
* * CONSTRUCTOR WITH DDX AND DDY
* *********************************/
Acceleration::Acceleration(double ddx, double ddy) : ddx(0.0), ddy(0.0)
{
   setDDX(ddx);
   setDDY(ddy);
}
/*******************************************
*COMPUTE ACCELERATION
*
*******************************************/

double Acceleration::getAcceleration() const
{
   return sqrt((ddx * ddx) + (ddy * ddy));
}

double Acceleration::computeDDX(double total, Angle a)
{
   return -sin(a.getRadians()) * total;
}

double Acceleration::computeDDY(double total, Angle a)
{
   return -cos(a.getRadians()) * total;
}