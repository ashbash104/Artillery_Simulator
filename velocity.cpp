/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Ashlee Hart
 ************************************************************************/

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>            // for sin and cos

 /******************************************
  * VELOCITY : CONSTRUCTOR WITH DX,DY
  * Initialize velocity to the passed dx
  * and dy
  *****************************************/
Velocity::Velocity(double dx, double dy) : dx(0.0), dy(0.0)
{
   setDX(dx);
   setDY(dy);
}

/******************************************
 * VELOCITY : CONSTRUCTOR WITH SPEED, ANGLE
 * Initialize velocity using the passed speed
 * and angle
 *****************************************/
Velocity::Velocity(double speed, Angle angle)
{
   dx = sin(angle.getRadians()) * speed;
   dy = cos(angle.getRadians()) * speed;
}

/*********************************************
 TOTAL CURRENT VELOCITY
 *********************************************/
long double Velocity::getSpeed() const
{
   return sqrt((dx * dx) + (dy * dy));
}

/*********************************************
 * ADD VELOCITY
 *********************************************/
void Velocity::addVelocity(const Velocity& v)
{
   dx += v.getDX();
   dy += v.getDY();
}

/*********************************************
 * ADD ACCELERATION
 *********************************************/
void Velocity::addAcceleration(const Acceleration& a, long double t)
{
   dx += a.getDDX() * t;
   dy += a.getDDY() * t;
}

/*********************************************
 * UPDATE VELOCITY WITH DX
 *********************************************/
void Velocity::addDX(double dx)
{
   this->dx += dx;
}

/*********************************************
 *UPDATE VELOCITY WITH DY
 *********************************************/
void Velocity::addDY(double dy)
{
   this->dy += dy;
}