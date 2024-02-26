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
 * VELOCITY : GET SPEED
 * Return the total current velocity
 *    x^2 + y^2 = t^2
 *********************************************/
long double Velocity::getSpeed() const
{
   return sqrt((dx * dx) + (dy * dy));
}

/*********************************************
 * VELOCITY : ADD VELOCITY
 * vector addition
 *********************************************/
void Velocity::addVelocity(const Velocity& v)
{
   dx += v.getDX();
   dy += v.getDY();
}

/*********************************************
 * VELOCITY : ADD
 * Given an existing velocity, update it
 * with added acceleration and time
 *********************************************/
void Velocity::addAcceleration(const Acceleration& a, long double t)
{
   dx += a.getDDX() * t;
   dy += a.getDDY() * t;
}

/*********************************************
 * VELOCITY : ADD DX
 * Given an existing velocity, update it
 * with added horizontal velocity
 *********************************************/
void Velocity::addDX(double dx)
{
   this->dx += dx;
}

/*********************************************
 * VELOCITY : ADD DY
 * Given an existing vel ocity, update it
 * with added vertical velocity
 *********************************************/
void Velocity::addDY(double dy)
{
   this->dy += dy;
}