#ifndef TIMER_H
#define TIMER_H


class Timer{
  public:
    Timer();
    void update(unsigned long nowTime);
    void setInterval(void (*t) (int t),long time);
  private:
    void (*frame) (int t);
    long preTime;
    long frameTime; 
};

#endif