#pragma once
/***********************************************************************
 * Header File:
 *    Angle
 * Author:
 *    Ashlee Hart
 ************************************************************************/

#pragma once

#include <iostream>
using namespace std;
#define _USE_MATH_DEFINES    // for M_PI
#include <math.h>

/*********************************************
 * Angle Class
 *********************************************/
class Angle
{
private:
   // member variables
   double radians;

public:
   // constructors
   Angle() : radians(0.0) {}
   Angle(const Angle& rhs) { radians = rhs.radians; }

   double convertToDegrees(double radians) const;
   double convertToRadians(double degrees) const;
   void normalize();

   // getters
   double getDegrees() const { return convertToDegrees(radians); }
   double getRadians() const { return radians; }

   // setters
   void setDegrees(double degrees);
   void setRadians(double radians);
   void addDegrees(double degrees);
   void addRadians(double radians);
   void assign(Angle rhs) { setRadians(rhs.getRadians()); }
   void setDown() { setRadians(M_PI); }
   void setUp() { setRadians(0.0); }
   void setLeft() { setRadians(-M_PI / 2); }
   void setRight() { setRadians(M_PI / 2); }
   void reverse();

   //void display() const;
};