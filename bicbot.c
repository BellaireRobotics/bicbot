#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
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
#pragma config(Motor,  port10,          leftIntake,    tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"

//
// LEAVE EVERYTHING ABOVE ALONE. THANKS.
//

// Math functions
#define SIGN(n) ((n > 0) ? 1 : ((n < 0) ? -1 : 0))
#define NORM(n) (127 * n / 10)

// Thresholds
#define THRESHOLD 15
#define LIFT_THRESHOLD 60

// Lift Constants
#define SETPOINT_0 4025
#define SETPOINT_1 2800
#define SETPOINT_2 1665
#define LIFT_LOWERLIM 4030
#define LIFT_UPPERLIM 1675

// Autonomous Pot Select Constants
#define AUTON_SELECT_NUM_OPTS 3

// Update the variables Y1, X1, X2 with current joystick values.
void update_drive_joyvals(int *Y1, int *X1, int *X2, int threshold) {
  if (abs(vexRT[Ch1]) > threshold) {
    *Y1 = vexRT[Ch1];
  } else {
    *Y1 = 0;
  }

  if (abs(vexRT[Ch4]) > threshold) {
    *X1 = vexRT[Ch4];
  } else {
    *X1 = 0;
  }

  if (abs(vexRT[Ch3]) > threshold) {
    *X2 = vexRT[Ch3];
  } else {
    *X2 = 0;
  }
}

// Set drive based on recored joystick values Y1, X1, X2.
void drive_set(int Y1, int X1, int X2) {
  motor[rightFront] = Y1 - X2 + X1;
  motor[rightMiddle] = X2 - Y1;
  motor[rightBack] =  Y1 - X2 - X1;
  motor[leftFront] = Y1 + X2 + X1;
  motor[leftMiddle] = X2 + Y1;
  motor[leftBack] =  Y1 + X2 - X1;
}

// Set drive motors independently.
void drive_set_ind(int rF, int rM, int rB, int lF, int lM, int lB) {
  motor[rightFront] = rF;
  motor[rightMiddle] = rM;
  motor[rightBack] = rB;
  motor[leftFront] = lF;
  motor[leftMiddle] = lM;
  motor[leftBack] = lB;
}

void forward(int speed) {
  drive_set_ind(speed, speed, speed, speed, speed, speed);
}

void reverse(int speed) {
  drive_set_ind(-speed, -speed, -speed, -speed, -speed, -speed);
}

void turn_right(int speed) {
  drive_set_ind(-speed, -speed, -speed, speed, speed, speed);
}

void turn_left(int speed) {
  drive_set_ind(speed, speed, speed, -speed, -speed, -speed);
}

void right(int speed) {
  // ...
}

void left(int speed) {
  // ...
}

void stop() {
  drive_set_ind(0, 0, 0, 0, 0, 0);
}

// Set lift motors to speed.
int lift_set(int speed) {
  motor[rightLift] = speed;
  motor[leftLift] = speed;

  return 0;
}

// Move lift to position.
int lift_set_position(int position) {
  int lift_triggered = vexRT[Btn5U] || vexRT[Btn5D] || vexRT[Btn7D] || vexRT[Btn7R] || vexRT[Btn7U] || \
                       vexRT[Btn5UXmtr2] || vexRT[Btn5DXmtr2] || vexRT[Btn7DXmtr2] || vexRT[Btn7RXmtr2] || \
                       vexRT[Btn7UXmtr2] || abs(vexRT[Ch3Xmtr2]);

  while (!lift_triggered) {
    if (abs(SensorValue[liftPot] - position) > LIFT_THRESHOLD) {
      lift_set((SensorValue[liftPot] - position) * 2);
    } else {
      lift_set(0);
    }
  }

  return 0;
}

// Set intake motors to speed.
void intake_set(int speed) {
  motor[rightIntake] = speed;
  motor[leftIntake] = speed;
}

// Autonomous selection.
int getopt_auton_select(int num_opts) {
  return (int)(SensorValue[auton_select] / num_opts);
}

// Safety task: Disable all motors whenever button combo is pressed.
task safety() {
  while (true) {
    if (vexRT[Btn7L] && vexRT[Btn8D]) {
      allMotorsOff();
    }
  }
}

// Drive task: Update current joyvals and set drive motors continuously.
task drive() {
  int Y1 = 0, X1 = 0, X2 = 0;

  while (true) {
    update_drive_joyvals(&Y1, &X1, &X2, THRESHOLD);
    drive_set(Y1, X1, X2);
  }
}

// Lift task: Button combos and waypoints.
task lift() {
  int curr_pos = 0, curr_pos_set = 0, pos_diff = 0;

  while (true) {
    if (SensorValue[liftPot] > LIFT_UPPERLIM && (vexRT[Btn5U] || vexRT[Ch3Xmtr2] > THRESHOLD)) {
      curr_pos_set = lift_set(vexRT[Btn5U] ? 127 : vexRT[Ch3Xmtr2]);
    } else if (SensorValue[liftPot] < LIFT_LOWERLIM && (vexRT[Btn5D] || vexRT[Ch3Xmtr2] < -THRESHOLD)) {
      curr_pos_set = lift_set(vexRT[Btn5D] ? -127 : vexRT[Ch3Xmtr2]);
    } else if (vexRT[Btn7D] || vexRT[Btn7DXmtr2]) {
      curr_pos_set = lift_set_position(SETPOINT_0);
    } else if (vexRT[Btn7R] || vexRT[Btn7RXmtr2]) {
      curr_pos_set = lift_set_position(SETPOINT_1);
    } else if (vexRT[Btn7U] || vexRT[Btn7UXmtr2]) {
      curr_pos_set = lift_set_position(SETPOINT_2);
    } else {
      if (!curr_pos_set) {
        curr_pos = SensorValue[lift_enc];
        curr_pos_set = 1;
      }

      pos_diff = SensorValue[lift_enc] - curr_pos;

      if (abs(pos_diff) > LIFT_THRESHOLD) {
        lift_set(pos_diff);
      } else {
        lift_set(pos_diff / 3);
      }
    }
  }
}

// Intake task.
task intake() {
  while (true) {
    if (vexRT[Btn6U] || -vexRT[Ch2Xmtr2] > THRESHOLD) {
      intake_set(vexRT[Btn6U] ? 127 : -vexRT[Ch2Xmtr2]);
    } else if (vexRT[Btn6D] || -vexRT[Ch2Xmtr2] < -THRESHOLD) {
      intake_set(vexRT[Btn6D] ? -127 : -vexRT[Ch2Xmtr2]);
    } else {
      intake_set(0);
    }
  }
}

// Write specific debugging values to stream.
task debug() {
  clearDebugStream();

  while (true) {
    if (SensorValue[auton_proceed1]) {
      writeDebugStreamLine("Left: %d\tRight: %d", SensorValue[lquad], SensorValue[rquad]);
      Sleep(1000);
    }
  }
}

// Stop teleop tasks.
task stop_for_auton() {
  StopTask(drive);
  StopTask(lift);
  StopTask(intake);
}


// Detect autonomous start for practice.
task auton_start_detect() {
  if (vexRT[Btn8U] && vexRT[Btn8R]) {
    StartTask(stop_for_auton);
    pre_auton();
    ClearTimer(T1);
    StartTask(autonomous);

    while (time100[T1] <= 15000 || !(vexRT[Btn8R] && vexRT[Btn8D])) {
      Sleep(500);
    }

    StartTask(usercontrol);
  }
}


// Ran once before autonomous.
void pre_auton() {
  // ...
}

// Autonomous task: Ran during 15 seconds of autonomous period.
task autonomous() {
  forward(127);
  Sleep(1000);
  stop();
}

// Usercontrol, basically main().
task usercontrol() {
  StopTask(autonomous); // kill autonomous task incase
  StartTask(safety);
  StartTask(drive);
  StartTask(lift); // do you even lift?!?!?!?!?!?!??! https://en.wikipedia.org/wiki/Lift_(mathematics)
  StartTask(intake);
  StartTask(auton_start_detect);
  StartTask(debug);
}
