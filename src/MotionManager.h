#ifndef ELYIR_MOWER_MOTION_MANAGER_H_
#define ELYIR_MOWER_MOTION_MANAGER_H_


// setup pins and other stuff
// create left and right motors controllers
// define forward motion
// define backward motion
// define leftTurn motion
// define rightTurn motion
// define stop control
// define zeroTurnLeft control
// define zeroTurnRight control
// define turnAroundRight control
// define turnAroundLeft control
// define zeroTurnAroundRight control
// define zeroTurnAroundLeft control

void ElyirMowerMotionManager_setup();
void ElyirMowerMotionManager_forward(int speedPercent);
void ElyirMowerMotionManager_backward (int speedPercent);
void ElyirMowerMotionManager_leftTurn (int speedPercent, bool reverse = false);
void ElyirMowerMotionManager_rightTurn (int speedPercent, bool reverse = false);
void ElyirMowerMotionManager_stop ();
void ElyirMowerMotionManager_zeroTurnLeft (int speedPercent, bool reverse = false);
void ElyirMowerMotionManager_zeroTurnRight (int speedPercent, bool reverse = false);

#endif  // ELYIR_MOWER_MOTION_MANAGER_H_