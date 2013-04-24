// Drive

#define DRIVE_JOY_THRESHOLD 15

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

void drive_set(int Y1, int X1, int X2) {
  motor[rightFront] = Y1 - X2 + X1;
  motor[rightMiddle] = X2 - Y1;
  motor[rightBack] =  Y1 - X2 - X1;
  motor[leftFront] = Y1 + X2 + X1;
  motor[leftMiddle] = X2 + Y1;
  motor[leftBack] =  Y1 + X2 - X1;
}

void drive_set_ind(int rF, int rM, int rB, int lF, int lM, int lB) {
  motor[rightFront] = rF;
  motor[rightMiddle] = rM;
  motor[rightBack] = rB;
  motor[leftFront] = lF;
  motor[leftMiddle] = lM;
  motor[leftBack] = lB;
}

void forward(int speed) {
  drive_set_ind(-speed, speed, -speed, speed, speed, speed);
}

void reverse(int speed) {
  forward(-speed);
}

void turn_right(int speed) {
  drive_set_ind(speed, -speed, speed, speed, speed, speed);
}

void turn_left(int speed) {
  turn_right(-speed);
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

task drive() {
  int Y1 = 0, X1 = 0, X2 = 0;

  while (true) {
    update_drive_joyvals(&Y1, &X1, &X2, DRIVE_JOY_THRESHOLD);
    drive_set(Y1, X1, X2);
  }
}
