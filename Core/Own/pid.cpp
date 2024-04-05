//
// Created by 24106 on 2024/4/5.
//

#include "pid.h"

void limit(float min,float &m,float max){
    if (min>m){
        m = min;
    } else if (max<m){
        m = max;
    }
}

float pid::PosPid(motor MOTOR, float target) {

    PItem = target - MOTOR.real;
    IItem += PItem;
    DItem = MOTOR.real - MOTOR.last_pos;

    return p * PItem + i * IItem + d * DItem;
}
float pid::AddPid(motor MOTOR, float target) {
    static float PreErr = 0;
    static float LastErr = 0;
    static float Err = 0;
/*
 * limit speed
 * can't too small
 * else
 * Turn left and right
 */
    limit(-30,target,30);

    PreErr = LastErr;
    LastErr = Err;
    Err = target - MOTOR.speed;

    limit(-10000,Err,10000);

    PItem = Err - LastErr;
    IItem = Err;
    DItem = Err - 2 * LastErr + PreErr;

    return p * PItem + i * IItem + d * DItem;
}

pid angle;
pid speed;
