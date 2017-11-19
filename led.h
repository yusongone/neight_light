#ifndef LED_H
#define LED_H

class LED{
  public:
    LED();
    char* update(unsigned int useTime);
    void breathe(int ms); //min:8 max:65535
    void setColor(float r,float g,float b);

  private:
    long breatheLoopTime;
    float index;
    float _power;
    char value[3];

    float rScale;
    float gScale;
    float bScale;

};

#endif