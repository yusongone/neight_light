#include "timer.h"
#include "Arduino.h"



Timer::Timer(){
  preTime=0;
};

void Timer::update(unsigned long nowTime){
  int _sub=nowTime-preTime;
  if(_sub>=frameTime){
    frame(_sub);
    preTime=nowTime;
  }
}

void Timer::setInterval(void (*test)(int t),long time){
  frame=test;
  frameTime=time;
}
