#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    auton_select,   sensorPotentiometer)
#pragma config(Sensor, in3,    line_track1,    sensorLineFollower)
#pragma config(Sensor, in4,    line_track2,    sensorLineFollower)
#pragma config(Sensor, dgtl1,  auton_proceed1, sensorTouch)
#pragma config(Sensor, dgtl2,  auton_proceed2, sensorTouch)
#pragma config(Sensor, dgtl3,  rquad,          sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  lquad,          sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  sonarOut,       sensorSONAR_cm)
#pragma config(Sensor, I2C_1,  lift_enc,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           rightIntake,   tmotorVex393, openLoop)
#pragma config(Motor,  port2,           rightFront,    tmotorVex393, openLoop)
#pragma config(Motor,  port3,           rightMiddle,   tmotorVex393, PIDControl, reversed, encoder, encoderPort, dgtl3, 1000)
#pragma config(Motor,  port4,           rightBack,     tmotorVex393, openLoop)
#pragma config(Motor,  port5,           rightLift,     tmotorVex393HighSpeed, PIDControl, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port6,           leftLift,      tmotorVex393HighSpeed, PIDControl, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port7,           leftFront,     tmotorVex393, openLoop)
#pragma config(Motor,  port8,           leftMiddle,    tmotorVex393, PIDControl, encoder, encoderPort, dgtl5, 1000)
#pragma config(Motor,  port9,           leftBack,      tmotorVex393, openLoop)
#pragma config(Motor,  port10,          leftIntake,    tmotorVex393, openLoop, reversed)

#include "Vex_Competition_Includes.c"

//
// LEAVE EVERYTHING ABOVE ALONE. THANKS.
//

//#include "safety.c"
#include "drive.c"
#include "lift.c"
#include "intake.c"
//#include "debug.c"
#include "autonomous.c"

task usercontrol() {
	StartTask(drive);
	StartTask(lift);
	StartTask(intake);
}
