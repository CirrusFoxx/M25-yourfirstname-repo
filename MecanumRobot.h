#ifndef MECANUMROBOT_H
#define MECANUMROBOT_H

#include <Arduino.h>

class MecanumRobot {
  public:
    MecanumRobot(int fl1, int fl2, int fr1, int fr2,
                 int rl1, int rl2, int rr1, int rr2)
      : FL1(fl1), FL2(fl2), FR1(fr1), FR2(fr2),
        RL1(rl1), RL2(rl2), RR1(rr1), RR2(rr2),
        turn90Time(500) {}

    void begin() {
      pinMode(FL1, OUTPUT); pinMode(FL2, OUTPUT);
      pinMode(FR1, OUTPUT); pinMode(FR2, OUTPUT);
      pinMode(RL1, OUTPUT); pinMode(RL2, OUTPUT);
      pinMode(RR1, OUTPUT); pinMode(RR2, OUTPUT);
      stop();
    }

    void forward(int time) {
      forwardStart();
      delay(time);
      stop();
    }

    void reverse(int time) {
      reverseStart();
      delay(time);
      stop();
    }

    void strafeRight(int time) {
      strafeRightStart();
      delay(time);
      stop();
    }

    void strafeLeft(int time) {
      strafeLeftStart();
      delay(time);
      stop();
    }

    void forwardStart() {
      leftForward();
      rightForward();
    }

    void reverseStart() {
      leftReverse();
      rightReverse();
    }

    void strafeRightStart() {
      motorForward(FL1, FL2);
      motorReverse(RL1, RL2);
      motorForward(FR1, FR2);
      motorReverse(RR1, RR2);
    }

    void strafeLeftStart() {
      motorReverse(FL1, FL2);
      motorForward(RL1, RL2);
      motorReverse(FR1, FR2);
      motorForward(RR1, RR2);
    }

    void turnLeftStart() {
      leftReverse();
      rightForward();
    }

    void turnRightStart() {
      leftForward();
      rightReverse();
    }

    void left(int degrees) {
      int total = (turn90Time * degrees) / 90;
      int elapsed = 0;
      while (elapsed < total) {
        turnLeftStart();
        delay(40);
        forwardStart();
        delay(10);
        elapsed += 50;
      }
      stop();
    }

    void right(int degrees) {
      int total = (turn90Time * degrees) / 90;
      int elapsed = 0;
      while (elapsed < total) {
        turnRightStart();
        delay(40);
        forwardStart();
        delay(10);
        elapsed += 50;
      }
      stop();
    }

    void stop() {
      leftStop();
      rightStop();
    }

    void setTurnTime(int t) {
      turn90Time = t;
    }

    void handleCommand(String input) {
      input.trim();
      int space = input.indexOf(' ');
      String cmd;
      int val = 0;
      if (space > 0) {
        cmd = input.substring(0, space);
        val = input.substring(space + 1).toInt();
      } else {
        cmd = input;
      }

      if (cmd == "forward") forward(val);
      else if (cmd == "reverse") reverse(val);
      else if (cmd == "left") left(val);
      else if (cmd == "right") right(val);
      else if (cmd == "strafeleft") strafeLeft(val);
      else if (cmd == "straferight") strafeRight(val);
      else if (cmd == "stop") stop();
    }

  private:
    int FL1, FL2, FR1, FR2, RL1, RL2, RR1, RR2;
    int turn90Time;

    void motorForward(int p1, int p2) {
      digitalWrite(p1, HIGH);
      digitalWrite(p2, LOW);
    }

    void motorReverse(int p1, int p2) {
      digitalWrite(p1, LOW);
      digitalWrite(p2, HIGH);
    }

    void motorStop(int p1, int p2) {
      digitalWrite(p1, LOW);
      digitalWrite(p2, LOW);
    }

    void leftForward() {
      motorForward(FL1, FL2);
      motorForward(RL1, RL2);
    }

    void leftReverse() {
      motorReverse(FL1, FL2);
      motorReverse(RL1, RL2);
    }

    void leftStop() {
      motorStop(FL1, FL2);
      motorStop(RL1, RL2);
    }

    void rightForward() {
      motorReverse(FR1, FR2);
      motorReverse(RR1, RR2);
    }

    void rightReverse() {
      motorForward(FR1, FR2);
      motorForward(RR1, RR2);
    }

    void rightStop() {
      motorStop(FR1, FR2);
      motorStop(RR1, RR2);
    }
};

#endif
