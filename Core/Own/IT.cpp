//
// Created by 24106 on 2024/4/5.
//

#include "IT.h"
int  target = 2 * 899;

extern DMA_HandleTypeDef hdma_usart2_rx;

/**
 * @brief test function
 */
void test(){
    if (bag[0]=='@' && bag[1] == 'o'&& bag[2] == 'p' && bag[3] == 'e' && bag[4] == 'n'){
        if (bag[5]==' '&&bag[6]=='a'&&bag[7]=='n'&&bag[8]=='g'&&bag[9]=='l'&&bag[10]=='e') {
            left.clear();
            AngleOpen = 1;
        }
        else if (bag[5]==' '&&bag[6]=='s'&&bag[7]=='p'&&bag[8]=='e'&&bag[9]=='e'&&bag[10]=='d') {
            left.clear();
            SpeedOpen = 1;
        }
    } else if (bag[0]=='@' && bag[1] == 'c'&& bag[2] == 'l' && bag[3] == 'o' && bag[4] == 's' && bag[5] == 'e'){
        if (bag[6]==' '&&bag[7]=='a'&&bag[8]=='n'&&bag[9]=='g'&&bag[10]=='l'&&bag[11]=='e') {
            AngleOpen = 0;
        }
        else if (bag[6]==' '&&bag[7]=='s'&&bag[8]=='p'&&bag[9]=='e'&&bag[10]=='e'&&bag[11]=='d') {
            SpeedOpen = 0;
        }
    }
}

float myabs(float input){
    return input<0?-input:input;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    if (huart==&huart2){

        print(&huart2,"bag:%s\n",bag);

        if (bag[0]=='@'){
            angle.clear();
            speed.clear();
            speed_alone.clear();
            print(&huart2,"%s\n","get the struct");
            number((char *)(bag), &target);
            print(&huart2,"target:%d\n",target);
        }
        test();

        HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t *)bag, 50);
        __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);

    }
}





void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim == &htim2){
        left.GetPos();

        if (AngleOpen) {
            if (myabs(left.real - target) <= 3)
                left.SetPwm(0);
            else {
                print(&huart2, "@%hd@%d@%hd@%hd\n", left.speed, left.real, left.pos, left.last_pos);
                left.SetPwm(speed.AddPid(left, angle.PosPid(left, target)));
            }
        }

        if (SpeedOpen){
            left.SetPwm(speed_alone.SpeedPid(left, target));
            print(&huart2,"@%hd@%d@%hd@%hd\n",left.speed,left.real,left.pos,left.last_pos);
        }

    }
};
