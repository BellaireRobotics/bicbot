// Safety task: Disable all motors whenever button combo is pressed.
task safety() {
  while (true) {
    if (vexRT[Btn7U] && vexRT[Btn7L] && vexRT[Btn7R] && vexRT[Btn7D] && \
        vexRT[Btn8U] && vexRT[Btn8L] && vexRT[Btn8R] && vexRT[Btn8D] && \
        vexRT[Btn5U] && vexRT[Btn5D] && vexRT[Btn6U] && vexRT[Btn6D]) {
      allMotorsOff();
    }
  }
}
