#ifndef BASE_H
#define BASE_H
#include<iostream>
#include<cstring>

void FCFS();
void SSTF();
void SCAN();

typedef struct node{
    int position;
    bool stsation;//1是 0不是
    struct node * ccwise;
    struct node * wise;
}ROU;

ROU * creatroutine();

void getorder();//获取指令

void print();//打印状态
#endif