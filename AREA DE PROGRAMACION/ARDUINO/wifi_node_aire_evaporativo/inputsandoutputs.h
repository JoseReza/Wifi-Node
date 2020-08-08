#ifndef INPUTANDOUTPUTS_H
#define INPUTANDOUTPUTS_H

int lowVelocityPin = 4;
int mediumVelocityPin = 0;
int highVelocityPin = 2;
int waterPumpPin = 15;

void inputsAndOutputsStart(){
  pinMode(lowVelocityPin, OUTPUT);
  pinMode(mediumVelocityPin, OUTPUT);
  pinMode(highVelocityPin, OUTPUT);
  pinMode(waterPumpPin, OUTPUT);
}
#endif
