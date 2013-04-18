// Stop teleop tasks.
task stop_for_auton() {
  StopTask(drive);
  StopTask(lift);
  StopTask(intake);
}


// Detect autonomous start for practice.
task auton_start_detect() {
  while (true) {
    if (vexRT[Btn7L] && vexRT[Btn8R]) {
      StartTask(stop_for_auton);
      pre_auton();
      StartTask(autonomous);
      Sleep(30000);
      StartTask(usercontrol);
    }
  }
}

void getFiveStack() {
  intake_set(127);
  forward(127);
  Sleep(2000);
  stop();
  Sleep(1000);
  reverse(127);
  Sleep(2000);
  stop();
  intake_set(0);
}

void score() {
  forward(127);
  Sleep(3500);
  lift_set_position(HIGHGOAL);
  stop();
  intake_set(-127);
  Sleep(500);
  reverse(127);
  Sleep(3500);
  lift_set_position(FLOORPOINT);
  Sleep(3500);
}

void auton_get_next() {
  while (true) {
    if (SensorValue[auton_proceed1]) {
      getFiveStack();
      break;
    } else if (SensorValue[auton_proceed2]) {
      score();
      break;
    }
  }
}

// Ran once before autonomous.
void pre_auton() {
  // ...
}

// Autonomous task: Ran during 15 seconds of autonomous period.
task autonomous() {
  getFiveStack();

  while (true) {
    auton_get_next();
  }
}
