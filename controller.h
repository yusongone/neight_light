#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "WS2812.h"
#include "led.h"


class Controller{
  public:
    Controller(uint16_t number);
    void setOutpin(uint8_t pin);
    void update(unsigned int time);
    void ChangeType(char type);
    int* getRgb(float);

  private:
    void intervalHandler(unsigned int useTime);
    void rotate(unsigned int useTime);
    void breathe(unsigned int useTime);
    unsigned char type=0x01;
    unsigned long preTime=0;
    unsigned int index=0;

    unsigned int breathe_time;
    unsigned int rotate_group_led_count;

    WS2812 *P_LED;
    cRGB rgb;
    LED* leds;
    uint16_t ledZCount;
};


#endif

