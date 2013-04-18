// Lift "PID" Function
#define LIFT(diff) (-180+42*log(diff))

// Lift Constants
#define LIFT_THRESHOLD 120
#define LIFT_JOY_THRESHOLD 15
#define FLOORPOINT 4095
#define LOWGOAL 2750
#define HIGHGOAL 1760
#define LIFT_LOWERLIM 4095
#define LIFT_UPPERLIM 1575

// Set lift motors to speed.
int lift_set(int speed) {
  motor[rightLift] = speed;
  motor[leftLift] = speed;

  return 0;
}

// Move lift to position.
int lift_set_position(int position) {
  int lift_triggered = 0;
  int lift_diff = 0;

  ClearTimer(T2);

  while (!lift_triggered) {
    if (abs(SensorValue[liftPot] - position) > LIFT_THRESHOLD) {
      lift_diff = SensorValue[liftPot] - position;
      lift_set(sgn(lift_diff)*LIFT(abs(lift_diff)));
    } else {
      lift_set(0);
    }

    lift_triggered = vexRT[Btn5U] || vexRT[Btn5D] || vexRT[Btn5UXmtr2] || vexRT[Btn5DXmtr2] || \
                     abs(vexRT[Ch3Xmtr2]) > LIFT_JOY_THRESHOLD || \
                     ((vexRT[Btn7U] || vexRT[Btn7R] || vexRT[Btn7D] || \
                       vexRT[Btn7UXmtr2] || vexRT[Btn7RXmtr2] || vexRT[Btn7DXmtr2]) && time1[T2] >= 500);
  }

  return 0;
}

// Lift task: Button combos and waypoints.
task lift() {
  int curr_pos = 0, curr_pos_set = 0, pos_diff = 0;

  while (true) {
    if (SensorValue[liftPot] > LIFT_UPPERLIM && (vexRT[Btn5U] || vexRT[Btn5UXmtr2] || vexRT[Ch3Xmtr2] > LIFT_JOY_THRESHOLD)) {
      curr_pos_set = lift_set(vexRT[Btn5U] || vexRT[Btn5UXmtr2] ? 127 : vexRT[Ch3Xmtr2]);
    } else if (SensorValue[liftPot] < LIFT_LOWERLIM && (vexRT[Btn5D] || vexRT[Btn5DXmtr2] || vexRT[Ch3Xmtr2] < -LIFT_JOY_THRESHOLD)) {
      curr_pos_set = lift_set(vexRT[Btn5D] || vexRT[Btn5DXmtr2] ? -127 : vexRT[Ch3Xmtr2]);
    } else if (vexRT[Btn7D] || vexRT[Btn7DXmtr2]) {
      curr_pos_set = lift_set_position(FLOORPOINT);
    } else if (vexRT[Btn7R] || vexRT[Btn7RXmtr2]) {
      curr_pos_set = lift_set_position(LOWGOAL);
    } else if (vexRT[Btn7U] || vexRT[Btn7UXmtr2]) {
      curr_pos_set = lift_set_position(HIGHGOAL);
    } else if (vexRT[Btn8U] || vexRT[Btn8UXmtr2]) {
      curr_pos_set = lift_set(127);
    } else if (vexRT[Btn8D] || vexRT[Btn8DXmtr2]) {
      curr_pos_set = lift_set(-127);
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
