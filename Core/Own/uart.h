//
// Created by 24106 on 2024/4/5.
//

#ifndef ANGLE_UART_H
#define ANGLE_UART_H

#include "usart.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"

extern uint8_t bag[15];   //指定集 //data bag
extern uint8_t first; //验证包头@，在结束收包时清除标记@置1 //the first receive byte, if it receives '@', then receive data bag, else nothing
extern uint8_t val; //验证是否是数据包 //it tells the program whether receive the data bag
extern uint8_t i;  //包数组的位置 //it is the data bag's index
extern uint8_t out; //数据包超过10个的检验结束标志！ //it tells the program whether the data bag is more than 10 bytes,if it happens, the program will not receive the data bag and will do loop until receive the last byte '!'
extern uint8_t open;


void print(UART_HandleTypeDef* huart, const char* buf, ...);
void number(const char* str,int *s,int *p);
uint8_t ReceiveBag();
void test();

#endif //ANGLE_UART_H
