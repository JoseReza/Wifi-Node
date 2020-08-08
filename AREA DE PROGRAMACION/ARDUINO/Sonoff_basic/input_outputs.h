#ifndef INPUTS_OUTPUTS_H
#define INPUTS_OUTPUTS_H

int rele = 12;
int boton = 0;
int led = 13;
int sensor = 2;

void inputAndOutputsStart(){
  pinMode(rele, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(boton, INPUT);
  pinMode(sensor, INPUT);
}

#endif
