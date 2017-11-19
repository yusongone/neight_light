#include "led.h";
#include "Arduino.h";


LED::LED(){
  _power=0;
  index=0;
  breatheLoopTime=0;
  value[0]=0;
  value[1]=0;
  value[2]=0;

  rScale=1;
  gScale=1;
  bScale=1;
}

void LED::breathe(int ms){
  breatheLoopTime=ms;
}

void LED::setColor(float r,float g,float b){
  rScale=min(1, max(r,0));
  gScale=min(1, max(g,0));
  bScale=min(1, max(b,0));
}


char* LED::update(unsigned int useTime){
  if(breatheLoopTime!=0){
    index+=254*float(useTime)/breatheLoopTime;
    if(index>=254){
      index=0;
      breatheLoopTime=0;
    }
    float k1=(255-2*abs(127-index))/255;
    float k2=(1-cos((index/255)*6.283185307179586))/2;
    _power=127.5-(127.5*cos(index*6.283185307179586/255));
    _power=_power*k2*k1;
    value[0]=1;
    value[1]=0;
    value[2]=0;
    /*
    value[0]=int(_power*rScale);
    value[1]=int(_power*gScale);
    value[2]=int(_power*bScale);
    */
  }

  return value;
}
