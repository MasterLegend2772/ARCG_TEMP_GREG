#include "vex.h"
#include "screen.h"
#include "util.h"
#include "Drive.h"
#include "PID.h"

using namespace vex;

///////////////////////// Prototypes /////////////////////////////////

void rise();
void fall();
void outTake();
void usercontrol();

//////////////////////////////////////////////////////////////////////

bool armUp = false;
int lastPressed = 0;

bool isInAuton = false;

float velocity = 12.0;
bool boost = true;

int odomType = NO_ODOM;

bool isBottomOuttakeRunning = false;
