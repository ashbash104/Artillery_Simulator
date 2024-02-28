#pragma once
/***********************************************************************
 * Header File:
 *    VELOCITY
 * Author:
 *    Ashlee HArt
 ************************************************************************/


#pragma once

#include "acceleration.h" // for add()
#include "angle.h" 
#include <math.h>         // for sqrt()


/*********************************************
 * VELOCITY
 *********************************************/
class Velocity
{
private:
   // member variables
   double dx;
   double dy;

public:
   // constructors
   Velocity() : dx(0.0), dy(0.0) {}
   Velocity(double dx, double dy);
   Velocity(double speed, Angle angle);

   // getters
   long double getDX()    const { return dx; } 
   long double getDY()    const { return dy; } 
   long double getSpeed() const;

   // setters
   void setDX(const long double& dx) { this->dx = dx; }
   void setDY(const long double& dy) { this->dy = dy; }


   //methods
   void addAcceleration(const Acceleration& a, long double t);
   void addVelocity(const Velocity& v);
   void addDX(double dx);
   void addDY(double dy);
   void reverse() { setDY(-dy); setDX(-dx); }

};