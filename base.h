#ifndef MAIN_CPP_BASE_H
#define MAIN_CPP_BASE_H

#include<iostream>
#include<cstring>
using namespace std;

extern int TOTAL_STATION;
extern string STRATEGY;
extern int DISTANCE;
extern int direction;//0->cwise,1->ccwise
extern int door;
extern string order;

typedef struct node{
    int position;
    int station; //代表站点编号，若为-1表示不是站点
    struct node * ccwise;
    struct node * wise;
}ROAD;

ROAD * creatroutine();
ROAD * appendNode(ROAD* head, int pos);
extern ROAD * head;
extern ROAD * bus;

void config();
void FCFS();
void SSTF();
void SCAN();
void getorder();//获取指令
void action();

#endif