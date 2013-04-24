//Intake

#define INTAKE_JOY_THRESHOLD 15

void intake_set(int speed) {
  motor[rightIntake] = speed;
  motor[leftIntake] = speed;
}

task intake() {
  while (true) {
    if (vexRT[Btn6U] || vexRT[Btn6UXmtr2] || -vexRT[Ch2Xmtr2] > INTAKE_JOY_THRESHOLD) {
      intake_set(vexRT[Btn6U] || vexRT[Btn6UXmtr2] ? 127 : -vexRT[Ch2Xmtr2]);
    } else if (vexRT[Btn6D] || vexRT[Btn6DXmtr2] || -vexRT[Ch2Xmtr2] < -INTAKE_JOY_THRESHOLD) {
      intake_set(vexRT[Btn6D] || vexRT[Btn6DXmtr2] ? -127 : -vexRT[Ch2Xmtr2]);
    } else {
      intake_set(0);
    }
  }
}
