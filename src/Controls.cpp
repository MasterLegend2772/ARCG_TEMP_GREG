#include "Controls.h"

Drive chassis
(
    motor_group(L1, L2, L3, L4), // Left drive train motors 
    motor_group(R1, R2, R3, R4), // Right drive train motors
    PORT8,               // Inertial Sensor Port
    2.75,              // The diameter size of the wheel in inches
    1,                   // 
    velocity,                   // The maximum amount of the voltage used in the drivebase (1 - 12)
    odomType,
    1,                  //Odometry wheel diameter (set to zero if no odom) (1.96 robot behind by .2)
    0,               //Odom pod1 offset 
    0                //Odom pod2 offset
);

//Outtake function   ********HAVE SOMEONE LOOK AT HOW COLOR SORT MODIFIED THIS*********
void outTake() {
  if (!revolver.isSpinning()) {
    armUp = true;

    outtake.setVelocity(50, percent);
    outtake.spinToPosition(90, degrees, true);
    // outtake.spinToPosition(0, degrees, false);
    outtake.spinFor(reverse, 1, sec);
    outtake.stop(hold);
    armUp = false;
    moveSlot();
  }
}

void bottomOuttakeFunction()
{
  if(!revolver.isSpinning())
  {
    isBottomOuttakeRunning = true;
    armUp = true;
    intake.spin(reverse, 12, volt);
    bottomOuttake.setVelocity(100, percent);
    bottomOuttake.spinToPosition(200, degrees, true);
    bottomOuttake.spin(reverse, 12, volt);
    wait(0.8, sec);
    bottomOuttake.stop(hold);
    //intakeLeft.spin(reverse, 0, volt);
    //intakeRight.spin(reverse, 0, volt);
    armUp = false;
    isBottomOuttakeRunning = false;

    // revolverSlots[0][0] = 0;
    // revolverSlots[0][1] = 0;
    // revolverSlots[0][2] = 0;
  }
}

void moveIntake()
{
  if(!revolver.isSpinning())
  {
    intake.spin(forward, 12, volt);
  }
}

void matchLoad() {
  matchLoader.set(true);
  moveIntake();
  wait(1.5, sec);
  intake.stop(hold);
  matchLoader.set(false);
}

//function to unload all
void unloadAll() {
  for(int i = 0; i <6; i++)
      {
        outTake();
        waitUntil(!revolver.isSpinning());
      }
}


// Check Canister
bool isSlotFull()
{
  //Says, "If frontSensor is between 0 and 20(red), or frontSensor is between 170 and 200(blue)"
  //AND "MiddleSensor is red or blue"
  //AND "BackSensor is red or blue"
  //Then return that Slot is full (true)
  if((((frontColorSensor.hue() <= 20 && frontColorSensor.hue() >= 0)) ||
    ((frontColorSensor.hue() <= 170 && frontColorSensor.hue() >= 200))) &&
    (((middleColorSensor.hue() <= 20 && middleColorSensor.hue() >= 0)) ||
    ((middleColorSensor.hue() <= 170 && middleColorSensor.hue() >= 200))) &&
    (((backColorSensor.hue() <= 20 && backColorSensor.hue() >= 0)) || 
    ((backColorSensor.hue() <= 170 && backColorSensor.hue() >= 200))))
    {
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("Is Full");
      return true;
    }
  else 
    return false;
}


/******************************************************************
 * Function: FixGeneva()
 * Purpose: Reverse Rotate Geneva while button is pressed
*****************************************************************/
void FixGeneva() 
{
  if(!revolver.isSpinning())
    revolver.spin(reverse, 8, volt);
}

void setBoost() {
  if (!boost) {
    velocity = 12.0;
    boost = true;
  } else if (boost) {
    velocity = 1.0;
    boost = false;
  }
}

void moveSlot()
{
  //SetSlot(); //Sets the colors in the 2D array for each slot
  //transferArrayInfo();
  revolver.setTimeout(0.55, seconds);
  revolver.setVelocity(100, percent);
  revolver.spinFor(1, rev);
}

// Check Canister
bool isSlotFull();

/// @brief Runs during the UserControl section of the competition
void usercontrol() 
{
  isInAuton = true;
  extendo.set(true);

  R1.setBrake(coast);
  R2.setBrake(coast);
  R3.setBrake(coast);
  R4.setBrake(coast);
  L1.setBrake(coast);
  L2.setBrake(coast);
  L3.setBrake(coast);
  L4.setBrake(coast);

  outtake.spin(reverse, 9, volt);
  wait(0.1, sec);
  outtake.stop(hold);

  Brain.Screen.clearScreen();
  bool isSpinning = false;

  //Team select function - note: this changes depending on the slot
  //teamColorSelect(teamColor); // Team selected

  Controller1.ButtonUp.pressed(rise);
  Controller1.ButtonDown.pressed(fall);
  backColorSensor.setLight(ledState::on);
  middleColorSensor.setLight(ledState::on);
  frontColorSensor.setLight(ledState::on);

  Controller1.ButtonR1.pressed(outTake);
  Controller1.ButtonR2.pressed(bottomOuttakeFunction);

  Controller1.ButtonL1.pressed(moveIntake);
  Controller1.ButtonL2.pressed(moveIntake);

  Controller1.ButtonLeft.pressed(FixGeneva);


  Controller1.ButtonX.pressed(setBoost);

  // User control code here, inside the loop
  while (1) 
  {
    extendo.set(true);

    //To stop geneva fixer from spinning when button is released
    if(!Controller1.ButtonLeft.pressing())
    {
      revolver.spin(forward, 0, volt);
    }

    if(Controller1.ButtonB.pressing() && !revolver.isSpinning())
    {
      if(armUp == false) {
        moveSlot();
      }
    }

    //Automatic Rotation
    if((Controller1.ButtonL1.pressing() || Controller1.ButtonL2.pressing()) && isSlotFull())
      {
        if(armUp == false) {
        moveSlot();
      }
     }

    if(Controller1.ButtonL2.pressing() && !revolver.isSpinning())
    {
      matchLoader.set(true);
    }
    else
    {
      matchLoader.set(false);
      if(!Controller1.ButtonL1.pressing() && !Controller1.ButtonR2.pressing())
      {
        intake.spin(reverse, 0, volt);
      }
    }

    chassis.arcade();
    wait(20, msec); // Sleep the task for a short amount of time to
    Brain.Screen.clearScreen();
  }

}
