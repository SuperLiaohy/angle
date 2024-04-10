//
// Created by 24106 on 2024/4/5.
//

#include "motor.h"
#include "uart.h"

void motor::front_run() {
    HAL_GPIO_WritePin(GPIOx,GPIO_Pin_1,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOx,GPIO_Pin_2,GPIO_PIN_RESET);
}

void motor::back_run() {
    HAL_GPIO_WritePin(GPIOx,GPIO_Pin_1,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOx,GPIO_Pin_2,GPIO_PIN_SET);
}

void motor::SetPwm(int input) {

    if (input>0){
        left.front_run();
    } else if (input<0){
        input = -input;
        left.back_run();
    }
    if (input==0)
        __HAL_TIM_SetCompare(pwm,Channel,0);
    else
        __HAL_TIM_SetCompare(pwm,Channel,input+350);

}

void motor::GetPos() {
    last_pos = pos;
    pos = __HAL_TIM_GET_COUNTER(encoder);
    speed = pos - last_pos;
    real += speed;
}

void motor::clear() {
    real = 0;
    pos = 0;
    last_pos = 0;
    speed = 0;
    __HAL_TIM_SET_COUNTER(encoder,0);
}

motor left(GPIOB,GPIO_PIN_0,GPIO_PIN_1,&htim1,TIM_CHANNEL_2,&htim3);