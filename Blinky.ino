/*
 * light_ws2812 example
 *
 * Created: 07.03.2014 12:49:30
 *  Author: Matthias Riegler
 */ 

#include "controller.h"
#include "timer.h"
#include "config.h"

Timer timer;
Controller controller(LED_COUNT);

unsigned long time=millis();

void run(int _time){
  controller.update(_time);
}

void setup() {
  Serial.begin(115200);
  controller.setOutpin(9); // Digital Pin 9
  timer.setInterval(&run,8);
}

void loop() {
  time=millis();
  timer.update(time);
  
}




