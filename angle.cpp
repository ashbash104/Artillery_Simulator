/***********************************************************************
 * Source File:
 *    Direction
 * Author:
 *    Ashlee Hart
 ************************************************************************/

#include "angle.h"

 /******************************************
  * DIRECTION :  CONVERT TO DEGREES
  * Convert radians to degrees:
  *     radians / 2pi = degrees / 360
  *****************************************/
double Angle::convertToDegrees(double radians) const
{
   return radians / (2.0 * M_PI) * 360.0;
}

/******************************************
 * DIRECTION : CONVERT TO RADIANS
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 *****************************************/
double Angle::convertToRadians(double degrees) const
{
   return (degrees / 360.0) * 2.0 * M_PI;
}

/******************************************
 *NORMALIZE
 *****************************************/
void Angle::normalize()
{
   while (radians > M_PI * 2)
      setRadians(radians - (M_PI * 2.0));
   while (radians < -(M_PI * 2))
      setRadians(radians + (M_PI * 2.0));
}

/******************************************
 * SET DEGREES
 *****************************************/
void Angle::setDegrees(double degrees)
{
   setRadians(convertToRadians(degrees));
}

/******************************************
 * SET RADIANS
 *****************************************/
void Angle::setRadians(double r)
{
   radians = r;
   normalize();
}

/******************************************
 * ADD RADIANS TO ANGLE
 *****************************************/
void Angle::addRadians(double radians)
{
   this->radians += radians;
   normalize();
}

/******************************************
 * ADD DEGREES
 *****************************************/
void Angle::addDegrees(double degrees)
{
   addRadians(convertToRadians(degrees));
}

/******************************************
 * REVERSE DIRECTION METHOD
 *****************************************/
void Angle::reverse()
{
   setRadians(radians + M_PI);
}