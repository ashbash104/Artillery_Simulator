/*************************************************************
 * 1. Name:
 *      Emily Raventos and Ashlee Hart
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      Setting up the program/getting it started.
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

 /*Test: Distance: 15976.4m   Altitude: 4280.88m */

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POSITION
#include <map>          // for linear interpolation
#include <math.h>       // for PI, sin, and cos
#include "angle.h"
#include "acceleration.h"
#include "velocity.h"
using namespace std;

#define INITIAL_VELOCITY 827.0
#define MASS 46.7
#define DIAMETER 0.15489
#define RADIUS 0.077445
//#define GRAVITY -9.80665
#define TIME 0.01
const double altitude = 0;
const double drag = 0;



/////**************************************************
////* COMPUTE HORIZONTAL VELOCITY
////* Input: Initial velocity
////* Output: dx
////**************************************************/
//double computeHorizontalVelocity()
//{
//   double dx = cos(radians) * INITIAL_VELOCITY; // If we get the wrong x, y (distance, altitude), apply m*a
//   return dx;
//}
//
/////**************************************************
////* COMPUTE VERTICAL VELOCITY
////* Input: Initial velocity
////* Output: dy
///**************************************************/
//double computeVerticalVelocity()
//{
//   dy = sin(radians) * INITIAL_VELOCITY;
//   return dy;
//}
/***************************************
*PROMPT
* Method to combine cout and cin
* Copied form last lab
**************************************/
double prompt(const string& message)
{
   double value = 0.0;
   cout << message;
   cin >> value;
   return value;
}
/******************************************
*LINEAR INTERPOLATION
* Input: 2 coordinate points
* Output:
* Does this need to be a long double?
*****************************************/
double linearInterpolate(double x0, double y0, double x1, double y1, double x)

{
   return y0 + ((x - x0) * (y1 - y0)) / (x1 - x0);
}

/*********************************
* LOOKUP VALUE
* If above is long double then this needs to be too
********************************/
double lookupValue(const std::map<double, double>& table, const double& value)
{
   if (value < table.begin()->first)
   {
      return table.begin()->second;
   }
   else if (value > table.rbegin()->first)
   {
      return table.rbegin()->second;
   }

   for (auto i = table.begin(); i != table.end(); i++)
   {
      if (i->first == value)
      {
         return i->second;
      }
      else if (i->first > value)
      {
         // ---> allows you to pass an array as an argument supposedly. 
         return linearInterpolate(i->first, i->second, i--->first, i->second, value);
      }
   }
   return 0.0;
}


/***********************************************
*COMPUTE DRAG COEFFICIENT
*
***********************************************/
double computeDrag(double drag)
{
   std::map<double, double> const dragChart
   {
      {0.300, 0.1629}, {0.500, 0.1659}, {0.700, 0.2031}, {0.890, 0.2597},
      {0.920, 0.3010}, {0.960, 0.3287}, {0.980, 0.4002}, {1.000, 0.4258},
      {1.020, 0.4335}, {1.060, 0.4483}, {1.240, 0.4064}, {1.530, 0.3663},
      {1.990, 0.2897}, {2.870, 0.2297}, {2.890, 0.2306}, {5.000, 0.2656}
   };
   return lookupValue(dragChart, drag);
}

/*********************************************
*COMPUTE DENSITY
* Input: altitude
* Output: The density of air at that altitude
*********************************************/
double computeDensity(const double& altitude)
{
   std::map<double, double> const densityChart
   {
         {    0.0, 1.2250000}, { 1000.0, 1.1120000}, { 2000.0, 1.0070000}, { 3000.0, 0.9093000},
         { 4000.0, 0.8194000}, { 5000.0, 0.7364000}, { 6000.0, 0.6601000}, { 7000.0, 0.5900000},
         { 8000.0, 0.5258000}, { 9000.0, 0.4671000}, {10000.0, 0.4135000}, {15000.0, 0.1948000},
         {20000.0, 0.0889100}, {25000.0, 0.0400800}, {30000.0, 0.0184100}, {40000.0, 0.0039960},
         {50000.0, 0.0010270}, {60000.0, 0.0003097}, {70000.0, 0.0000828}, {80000.0, 0.0000185}
   };
   return lookupValue(densityChart, altitude);
}


/*********************************************
*COMPUTE SPEED OF SOUND
* Input: altitude
* Output: The speed of sound at that altitude
*********************************************/
double computeSpeedofSound(const double& altitude)
{
   std::map<double, double> const soundChart
   {
         {    0.0, 340.0}, { 1000.0, 336.0}, { 2000.0, 332.0}, { 3000.0, 328.0},
         { 4000.0, 324.0}, { 5000.0, 320.0}, { 6000.0, 316.0}, { 7000.0, 312.0},
         { 8000.0, 308.0}, { 9000.0, 303.0}, {10000.0, 299.0}, {15000.0, 295.0},
         {20000.0, 295.0}, {25000.0, 295.0}, {30000.0, 305.0}, {40000.0, 324.0}
   };
   return lookupValue(soundChart, altitude);
}

/**********************************************
*COMPUTE GRAVITATIONAL FORCE
* Input: altitude
* Output: Gravity at that altitude
***********************************************/
double computeGravitationalForce(const double& altitude)
{
   std::map<double, double> const gravityChart
   {
         {    0.0, 9.807}, { 1000.0, 9.804}, { 2000.0, 9.801}, { 3000.0, 9.797},
         { 4000.0, 9.794}, { 5000.0, 9.791}, { 6000.0, 9.788}, { 7000.0, 9.785},
         { 8000.0, 9.782}, { 9000.0, 9.779}, {10000.0, 9.776}, {15000.0, 9.761},
         {20000.0, 9.745}, {25000.0, 9.730}
   };
   return lookupValue(gravityChart, altitude);
}

/**********************************************
*COMPUTE FORCE
*Input: drah, density, velocity, and area
* Output: the force of drag on the bullet
**********************************************/
double computeDragForce(const double& drag, const double& density,
   const double& velocity, const double& area)
{
   return 0.5 * (drag * density * velocity * velocity * area);
}

/**********************************************
*COMPUTE DECELRATION
* Do we need this?
**********************************************/
double computeDeceleration(const double& force, const double& mass)
{
   return force / MASS;
}

///*********************************************
//* COMPUTE NEW POSITION
//*
//*********************************************/
//double computeAltitude()
//{
//   return y + 214.043 + 0/*dy * time + 0.5 * (ddy * time * time)*/;
//
//}
//// FIX THIS FUNCTION TOO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//double computeDistance()
//{
//   return x + dx * time + 0.5 * (ddx * time * time);
//
//}

/*********************************
* CALCULATE ANGLE'Do we even need this?
********************************/
double computeAngle(double dx, double dy)
{
   return atan2(dx, dy);
}
/*******************************************
*COMPUTE AREA
*
*******************************************/
double computeArea(const double& radius)
{
   return M_PI * RADIUS * RADIUS;
}



/************************************
*SIMULATOR
* 
*************************************/
void simulate(Angle& angle, double& time, double& distance)
{
   Position pt = Position(0.0, 0.0);                        // The projectile's current position
   Position lastPt = Position();                            // The projectile's last known position
   Velocity v = Velocity(INITIAL_VELOCITY, angle);                 // The projectile's velocity
   double area = computeArea(DIAMETER / 2.0);       // Surface area of the front of the missile
   double total = 0.00;                                     // Total time passed since launch
   // Update the projectile's last known position
   lastPt = pt;
   do
   {
      // Update the environmental factors
      angle.setRadians(computeAngle(pt.getMetersX(), pt.getMetersY())); 
      double sound = computeSpeedofSound(pt.getMetersY());
      double mach = v.getSpeed() / sound;
      double drag = computeDrag(mach);
      double force = computeDragForce(drag, computeDensity(pt.getMetersY()),
         v.getSpeed(), area);
      double gravity = computeGravitationalForce(pt.getMetersY());

      // Update the projectile's position, velocity, and acceleration
      double acc = computeDeceleration(force, MASS);
      Acceleration acceleration(-sin(angle.getRadians()) * acc,
         -cos(angle.getRadians()) * acc - gravity);
      v.addAcceleration(acceleration, TIME);
      pt.addMetersX(v.getDX() * TIME + 0.5 * acceleration.getDDX() * TIME * TIME);
      pt.addMetersY(v.getDY() * TIME + 0.5 * acceleration.getDDY() * TIME * TIME);
      // Update the time passed
      total += TIME;
      cout << "X: " << pt.getMetersX() << "   Y: " << pt.getMetersY() << endl;

   }
   while (pt.getMetersY() >= 0.0); // Stop when we hit the ground
   if (pt.getMetersY() != 0)
   {
      distance = linearInterpolate(pt.getMetersX(), pt.getMetersY(), lastPt.getMetersX(), lastPt.getMetersY(),  0.0); // This isn't working :)))))
      time = linearInterpolate(pt.getMetersY(), total, lastPt.getMetersY(), total - TIME, 0.0);
   }
   else
   {
      distance = pt.getMetersX();
      time = total;
   }
}

int main()
{
   while (true)
   {
      int question;
      cout << "What is the angle of the Howitzer, where 0 is up?: ";
      cin >> question;

      Angle angle;
      angle.setDegrees(question);
      angle.convertToRadians(angle.getDegrees());
      //double radians = angle.getRadians();
      //Angle angle = Angle(prompt("What is the angle of the Howizter, where 0 is up?: ")); 
      double time = 0.0;
      double distance = 0.0; 
      simulate(angle, time, distance); 
      cout.setf(ios::fixed | ios::showpoint); 
      cout.precision(1); 
      cout << "Distance:\t" << distance << "m \tTime:\t" << time << "s" << endl; 
   }

} 