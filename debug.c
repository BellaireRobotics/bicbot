// Debug

task debug() {
  clearDebugStream();

  while (true) {
    if (SensorValue[auton_proceed1]) {
      writeDebugStreamLine("Left: %d\tRight: %d", SensorValue[lquad], SensorValue[rquad]);
      Sleep(1000);
    }
  }
}
