//
// Created by 24106 on 2024/4/5.
//

#include "IT.h"
int  target = 2 * 899;

float myabs(float input){
    return input<0?-input:input;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if (huart==&huart2){
        if (first == '@') {
            val = 1;
            if (i == 0) {
                for (int j = 1; j < 15; ++j) {
                    bag[j] = ' ';
                }
            }
            if (i > 0 && bag[i - 1] == '!' || out == '!') {
                if (out != '!')
                    bag[i - 1] = ' ';
                first = '1';
                out = ' ';
            } else if (i <= 14)
                HAL_UART_Receive_IT(&huart2, &bag[i++], 1);
            else
                HAL_UART_Receive_IT(&huart2, &out, 1);
        } else {
            first = '1';
            i = 0;
            val = 0;
        }
    }

}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim == &htim2){
        left.GetPos();
        print(&huart2,"@%hd@%d@%hd@%hd\n",left.speed,left.real,left.pos,left.last_pos);
        if (myabs(left.real - target)<=3)
            left.SetPwm(0);
        else
            left.SetPwm(speed.AddPid(left,angle.PosPid(left,target)));
    }
};
