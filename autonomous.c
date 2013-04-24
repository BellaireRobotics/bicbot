// Autonomous

task auton_lift_floor() {
  lift_set_position(FLOORPOINT);
  lift_set(15);
}

task auton_lift_lowgoal() {
  lift_set_position(LOWGOAL);
	lift_set(15);
}

void get_five_stack() {
	intake_set(-127);
	Sleep(270);
  intake_set(127);
  forward(127);
  Sleep(1650);
  stop();
  lift_set(-60);
  Sleep(420);
  lift_set(0);
  ClearTimer(T3);

  while (time1[T3] <= 1500) {
  	reverse(127);
  	Sleep(250);
  	forward(127);
  	Sleep(400);
	}

  Sleep(1000);
  reverse(127);
  Sleep(1950);
  stop();
  intake_set(0);
}

void score() {
  StartTask(auton_lift_lowgoal);
  Sleep(200);
  forward(127);
  Sleep(1900);
  stop();
  intake_set(-127);
  Sleep(3000);
  reverse(127);
  Sleep(1000);
  StartTask(auton_lift_floor);
  Sleep(1000);
  stop();
  intake_set(0);
}

void auton_get_next() {
  while (true) {
    if (SensorValue[auton_proceed1]) {
      get_five_stack();
      break;
    } else if (SensorValue[auton_proceed2]) {
      score();
      break;
    }
  }
}

void pre_auton() {
  // ...
}

task autonomous() {
  get_five_stack();

  while (true) {
    auton_get_next();
  }
}
