#ifndef BASE_H
#define BASE_H
#include<iostream>
#include<cstring>
using namespace std;

extern int TOTAL_STATION;
extern string STRATEGY;
extern int DISTANCE;
extern int direction;//0->cwise,1->ccwise
extern int pos;//short for position

void config();
void FCFS();
void SSTF();
void SCAN();

typedef struct node{
    int position;
    int station; //-1表示不是站点
    struct node * ccwise;
    struct node * wise;
}ROU;

ROU * creatroutine();

void getorder();//获取指令

void print();//打印状态

void action();

#endif