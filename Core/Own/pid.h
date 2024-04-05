
#ifndef ANGLE_PID_H
#define ANGLE_PID_H

#include "motor.h"

class pid{
private:
    float PItem;
    float IItem;
    float DItem;
public:

    float p;
    float i;
    float d;

    pid(float mp=0,float mi=0,float md=0):p(mp),i(mi),d(md){}

    float PosPid(motor MOTOR,float target);
    float AddPid(motor MOTOR,float target);
};


extern pid angle;
extern pid speed;



#endif //ANGLE_PID_H
