#ifndef ELYIR_MOWER_MANEUVER_H_
#define ELYIR_MOWER_MANEUVER_H_


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

void Elyir_Mower_Maneuver_setup();
void Elyir_Mower_Maneuver_forward();
void Elyir_Mower_Maneuver_backward ();
void Elyir_Mower_Maneuver_leftTurn ();
void Elyir_Mower_Maneuver_rightTurn ();
void Elyir_Mower_Maneuver_stop ();
void Elyir_Mower_Maneuver_zeroTurnLeft ();
void Elyir_Mower_Maneuver_zeroTurnRight ();
void Elyir_Mower_Maneuver_turnAroundRight ();
void Elyir_Mower_Maneuver_turnAroundLeft ();
void Elyir_Mower_Maneuver_zeroTurnAroundRight ();
void Elyir_Mower_Maneuver_zeroTurnAroundLeft ();
void Elyir_Mower_Maneuver_avoidObstacle ();

#endif  // ELYIR_MOWER_MANEUVER_H_