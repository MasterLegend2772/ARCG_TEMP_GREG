/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Organization:       Autonomous Robotics Club (ARC)                      */
/*    Authors:            Coby Smith and Joseph Dye                           */
/*    Created:            9/9/2024                                            */
/*    Description:        ARC Template                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "screen.h"
#include "util.h"
#include "Drive.h"
#include "PID.h"
#include "Auton.h"
#include "Controls.h"

using namespace vex;

////////////////////////// GLOBAL VARIABLES //////////////////////////

  // Competition Instance
  competition Competition;

  int odomType = NO_ODOM;

  float velocity = 12.0;
  float minVoltage = 1.4;
  bool boost = true;

  bool isInAuton = false;
  int lastPressed = 0;

  bool armUp = false;

  //Used for color sort
  const int blueTeam = 1;
  const int redTeam = 2;
  int teamColor = 1;

//////////////////////////////////////////////////////////////////////

///////////////////////// Prototypes /////////////////////////////////
void toggleDriveSpeed();
void SetSlot();
bool TopSlotMajorityEnemy(int);
void transferArrayInfo();
void AutonSkills_Left();


//////////////////////////////////////////////////////////////////////

//Rise!!
void rise() {

  liftL.set(true);
  wait(10, msec);
  liftR.set(true);
}

//Fall!
void fall() {

  liftL.set(false);
  liftR.set(false);
}


int main() 
{

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  preAuton();

  // Prevent main from exiting with an infinite loop.
  while (true) 
  {
    wait(100, msec);
  }
}






