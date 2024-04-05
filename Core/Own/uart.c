//
// Created by 24106 on 2024/4/5.
//

#include "uart.h"

/*
 * global variable
 */

uint8_t bag[15] = "         ";   //指定集 //data bag
uint8_t first = '1'; //验证包头@，在结束收包时清除标记@置1 //the first receive byte, if it receives '@', then receive data bag, else nothing
uint8_t val; //验证是否是数据包 //it tells the program whether receive the data bag
uint8_t i=0;  //包数组的位置 //it is the data bag's index
uint8_t out=' '; //数据包超过10个的检验结束标志！ //it tells the program whether the data bag is more than 10 bytes,if it happens, the program will not receive the data bag and will do loop until receive the last byte '!'
uint8_t open = 0;
/*
 * tool
 * it can change int to string,
 * but can only 0~100
 */

void number(const char* str,int *s,int *p){
    int num=0;
    int val_fu=0;
    for (int i = 0; str[i] != 'b' ; ++i) {
        if (str[i]<='9'&&'0'<=str[i]){
            if (val_fu)
                num = num * 10 - (str[i] - '0');
            else
                num = num * 10 + (str[i] - '0');
        } else if (str[i]=='-'){
            val_fu = 1;
        } else{
            *s = num;
            num = 0;
            val_fu = 0;
        }
    }
    *p = num;
}






/*
 * receive data bag
 * the first is the '@'
 * and the last is the '!'
 * the maximum capacity of the data bag is 10 bytes;
 */

uint8_t ReceiveBag(){
    while (HAL_UART_Receive_IT(&huart2,&first,1));

    if (val){
        i=0;
        val = 0;
        return 1;
    }

    return 0;
}


void test(){
    if (bag[0] == 'p'&& bag[1] == 'i' && bag[2] == 'd'){
        open = 1;
    }
}


void print(UART_HandleTypeDef* huart, const char* buf, ...)
{
    const char *p = buf;
    char str[255] = {0};
    va_list v;
    va_start(v, buf);
    vsprintf(str, buf, v); //使用可变参数的字符串打印。类似sprintf
    HAL_UART_Transmit(huart, str, strlen(str), 0xff);
    va_end(v);
}




