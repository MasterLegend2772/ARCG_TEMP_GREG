#include "robot-config.h"

////////////// DO NOT REMOVE //////////////

// Defines the Brain and Controller
brain Brain;
controller Controller1;

///////////////////////////////////////////

//////////// Drive Train Motors ////////////

motor R1 = motor(PORT20, ratio6_1, true);
motor R2 = motor(PORT20, ratio6_1, true);
motor R3 = motor(PORT20, ratio6_1, true);
motor R4 = motor(PORT20, ratio6_1, true);
motor L1 = motor(PORT11, ratio6_1, false);
motor L2 = motor(PORT11, ratio6_1, false);
motor L3 = motor(PORT11, ratio6_1, false);
motor L4 = motor(PORT11, ratio6_1, false);

///////////////////////////////////////////

//System
motor revolver = motor(PORT10, ratio36_1, false);
motor outtake = motor(PORT1, ratio36_1, false);

//////////// Odometry Sensors ////////////
//TODO: CHANGE THE NAMES OF THESE
rotation rotation1 = rotation(PORT9);
rotation rotation2 = rotation(PORT2);

/////////////////////////////////////////

//////////// Inertial Sensors ////////////

inertial inertial1 = inertial(PORT6);

/////////////////////////////////////////