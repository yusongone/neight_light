#include "controller.h"
#include "config.h"



float getRandom(){
  return float(random(0,255))/255;
}


int getIndex(float _subIndex){
  _subIndex=_subIndex>=6?int(_subIndex)%6:int(_subIndex);
  return _subIndex;
}

int  getValue(float _index){
  int stepAry[]={255,255,255,0,0,0};
	int index=int(_index);
  index=index<0?360+index%360:index;
  index=index>=360?index%360:index;
  int subStep=stepAry[getIndex(index/60+1)]-stepAry[getIndex(index/60)];
  float stepIndex=long(_index*100)%6000;
  int t=int(stepIndex/6000*subStep+stepAry[int(index/60)]);
  return t;
}

int* Controller::getRgb(float index){
  //int rgb[3]={255,255,255};
  cRGB rgb;
  int* rgb=new int[3];
    rgb[0]=getValue(index+60);
    rgb[1]=getValue(index-180);
    rgb[2]=getValue(index-60);
  return rgb;
}

Controller::Controller(uint16_t number){
  ledZCount=number;
  leds = new LED[number];
  P_LED=new WS2812(number);

  breathe_time=BREATHE_TIME;
  rotate_group_led_count=ROTATE_GROUP_LED_COUNT;

  type=0x02;
  for(uint8_t i=0;i<number;i++){
    LED* l=new LED();
    leds[i]= *l;
    leds[i].setColor(255/255,float(100)/255,0);
  }
};

void Controller::setOutpin(uint8_t pin){
  P_LED->setOutput(pin);
}

void Controller::breathe(unsigned int useTime){
  long totalTime=preTime+useTime;
  if(totalTime>5000){

    for(unsigned char i=0;i<ledZCount;i++){
      int* f=getRgb(float(i)/ledZCount*360);
      leds[i].setColor(float(f[0])/255,float(f[1])/255,float(f[2])/255);
      leds[i].breathe(5000);
      delete[] f;
    }
    preTime=0;
  }else{
    preTime=totalTime;
  }
};

void Controller::rotate(unsigned int useTime){
  long totalTime=preTime+useTime;
  if(totalTime>ROTATE_LOOP_TIME/ledZCount){


    leds[index++].breathe(ROTATE_LOOP_TIME/ledZCount*rotate_group_led_count);
    preTime=0;

    if(index>=ledZCount){
      index=0;
    }
  }else{
    preTime=totalTime;
  }
};



void Controller::intervalHandler(unsigned int useTime){
  switch (type){
    case 0x01:
      rotate(useTime);
      break;
    case 0x02:
      breathe(useTime);
      break;
  }
}

void Controller::update(unsigned int useTime){
  intervalHandler(useTime);
  for(uint8_t i=0;i<ledZCount;i++){
    char *f = leds[i].update(useTime);
    rgb.r=f[0];
    rgb.g=f[1];
    rgb.b=f[2];
    P_LED->set_crgb_at(i,rgb);
  }
  P_LED->sync();
}


/*
  P_LED->set_crgb_at(index,rgb);
  P_LED->sync();
*/
