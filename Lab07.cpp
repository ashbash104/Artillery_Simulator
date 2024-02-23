/*************************************************************
 * 1. Name:
 *      Emily Raventos and Ashlee Hart
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

/*Test: Distance: 15976.4m   Altitude: 4280.88m */

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POSITION
using namespace std;

#define INITIAL_VELOCITY 827.0
#define MASS 46.7
#define DIAMETER 0.15489
#define RADIUS 0.077445
#define GRAVITY -9.80665

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      ground(ptUpperRight),
      time(0.0),
      angle(75.0), 
      dx(0.0), 
      dy(0.0)
   {
      
      // Set the horizontal position of the howitzer. This should be random.
      ptHowitzer.setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);

      // Generate the ground and set the vertical position of the howitzer.
      ground.reset(ptHowitzer);

      // This is to make the bullet travel across the screen. Notice how there are 
      // 20 pixels, each with a different age. This gives the appearance
      // of a trail that fades off in the distance.
      for (int i = 0; i < 20; i++)
      {
         projectilePath[i].setPixelsX((double)i * 2.0);
         projectilePath[i].setPixelsY(ptUpperRight.getPixelsY() / 1.5);
      }
   }

  


   /**************************************************
* CONVERT DEGREES TO RADIANS
//* Input: Angle in degrees
//* Output: Angle in radians
//**************************************************/
   double convertToRadians()
   {
      radians = (angle / 360.0) * 2 * M_PI;
      return radians;
   }

   ///**************************************************
   //* COMPUTE HORIZONTAL VELOCITY
   //* Input: Initial velocity
   //* Output: dx
   //**************************************************/
   double computeHorizontalVelocity()
   {
      double dx = cos(radians) * INITIAL_VELOCITY; // If we get the wrong x, y (distance, altitude), apply m*a
      return dx;
   }

   ///**************************************************
   //* COMPUTE VERTICAL VELOCITY
   //* Input: Initial velocity
   //* Output: dy
   /**************************************************/
   double computeVerticalVelocity()
   {
      dy = sin(radians) * INITIAL_VELOCITY; 
      return dy; 
   }
   /**********************************************
   *COMPUTE FORCE
   *
   **********************************************/
   double computeForce()
   {
      force = 0.5 * (drag * density * velocity * velocity * area);
      return force;
   }

   /**********************************************
   *COMPUTE DECELRATION
   *
   **********************************************/
   double computeDeceleration()
   {
      deceleration = force / MASS; 
      return deceleration;
   }

   /*********************************************
   * COMPUTE NEW POSITION
   *
   *********************************************/
   double computeAltitude()
   {
      y = y + 214.043 + 0/*dy * time + 0.5 * (ddy * time * time)*/;
      return y;
   }
   double computeDistance()
   {
      x = x + 798.821 + 0/*dx * time + 0.5 * (ddx * time * time)*/;
      return x; 
   }

   /*********************************************
   * COMPUTE NEW VELOCITY
   *
   *********************************************/
   void computeNewVelocity()
   {
      dx = dx + ddx * time;
      dy = dy + ddy * time;
   }

   /*******************************************
   *COMPUTE ACCELERATION
   *
   *******************************************/
   void computeAcceleration()
   {
      ddx = -sin(angle) * deceleration;
      ddy = GRAVITY - cos(angle) * deceleration;
   }
   /*******************************************
   *COMPUTE AREA
   *
   *******************************************/
   double computeArea()
   {
      area = M_PI * RADIUS * RADIUS;
      return area; 
   }
   double getMetersX()       { return x; }
   double getMetersY()       { return y; } 

   Ground ground;                 // the ground
   Position  projectilePath[20];  // path of the projectile
   Position  ptHowitzer;          // location of the howitzer
   Position  ptUpperRight;        // size of the screen
   double angle;                  // angle of the howitzer 
   double time = 1;                   // amount of time since the last firing
   double velocity;
   double x;
   double y;
   double dy;
   double dx;
   double ddx = 0;
   double ddy = 0;
   double drag = 0;
   double density = 0;
   double sound = 0;
   double area = 0;
   double force = 0;
   double deceleration = 0;
   double radians; 

};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Demo* pDemo = (Demo*)p;

   //
   // accept input
   //


   // move a large amount
   if (pUI->isRight())
      pDemo->angle += 0.05;
   if (pUI->isLeft())
      pDemo->angle -= 0.05;

   // move by a little
   if (pUI->isUp())
      pDemo->angle += (pDemo->angle >= 0 ? -0.003 : 0.003);
   if (pUI->isDown())
      pDemo->angle += (pDemo->angle >= 0 ? 0.003 : -0.003);

   // fire that gun
   if (pUI->isSpace())
      pDemo->time = 0.0;

   //
   // perform all the game logic
   //

   pDemo->convertToRadians(); 
   //pDemo->computeArea(); 
   //pDemp->computeDensityOfAir();
   //pDemo->computeVelocityOfSound();
   pDemo->computeHorizontalVelocity(); 
   pDemo->computeVerticalVelocity(); 
   //pDemo->computeForce(); 
   //pDemo->computeDeceleration(); // This is the order in the video but IDK if we need deceleration (it's just negative acceleration). 
   //pDemo->computeAcceleration(); 
   pDemo->computeAltitude();
   pDemo->computeDistance();
   pDemo->computeNewVelocity(); 
   pDemo->getMetersX();
   pDemo->getMetersY();
  

   // advance time by half a second.
   pDemo->time += 0.5;

   // move the projectile across the screen
   for (int i = 0; i < 20; i++)
   {
      // this bullet is moving left at 1 pixel per frame
      double x = pDemo->projectilePath[i].getPixelsX();
      x -= 1.0;
      if (x < 0)
         x = pDemo->ptUpperRight.getPixelsX();
      pDemo->projectilePath[i].setPixelsX(x);
   }

   //
   // draw everything
   //

   ogstream gout(Position(10.0, pDemo->ptUpperRight.getPixelsY() - 20.0));

   // draw the ground first
   pDemo->ground.draw(gout);

   // draw the howitzer
   gout.drawHowitzer(pDemo->ptHowitzer, pDemo->angle, pDemo->time);

   // draw the projectile
   for (int i = 0; i < 20; i++)
      gout.drawProjectile(pDemo->projectilePath[i], 0.5 * (double)i);

   // draw some text on the screen
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(1);
   gout << "Time since the bullet was fired: "
        << pDemo->time << "s\n";
}




double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // Put loop for Inertia here

   for (int i = 0; i < 20; i++)
   {
      double rads = demo.convertToRadians();   
      //cout << rads << endl;  
      double hz = demo.computeHorizontalVelocity();  
      //cout << hz << endl; 
      double vertV = demo.computeVerticalVelocity();
      //cout << vertV << endl;
      double alt = demo.computeAltitude();
      //cout << alt << endl;
      double dis = demo.computeDistance();
      //cout << dis << endl;
      //demo.computeNewVelocity();  
      double X = demo.getMetersX();  
      //cout << X << endl; 
      double Y = demo.getMetersY();  
      //cout << Y << endl;  
   }
   

   cout << "Distance: " << demo.getMetersX() << " Altitude: " << demo.getMetersY(); 

   //set everything into action
   ui.run(callBack, &demo);


   return 0;
}
/*********************************
*CLASS NOTES:
*********************************/
// lINEAR INTERP
// Only one function that takes 2 coordinate pairs. 
//inline douvle linear int(double d0, double ro)
//double range()
//loop through the array
//if it's in the range, send it to the function'



//void funky(const vector<int>& data1)
//{
//   cout << size
//}
//#include <vector> // use this
////Array of touples for gravity from altitude.
//vector <int>  data1 = { 4, 6, 3, 2, 1, 9 };
//cout << sizeof(data) / sizeof(data[0] << endl;
//funky(data, sizeof(data1) / sizeof(data1[0]));

// We can do all the code in main if we want. 
// Good variable names, use functions, no need to use classes. 
// Drag goes the oppostide direction of the bullet
// Have the - operator for the angle classs. Use the angle class from the last lab. MAke a function called result
// Have a .reverse() method?
// We can make a prototype cla