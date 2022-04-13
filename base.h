#include<iostream>
using namespace std;

int TOTAL_STATION =0;
char * STRATEGY=NULL;
int DISTANCE=0;
int pos=0;//short for position
//int tar=0;//short for target
//int wise[10];//short for clockwise
//int ccwise[10];//short for counterclockwise
//int time=0;

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
