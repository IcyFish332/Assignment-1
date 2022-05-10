#include"base.h"

void request_for_SCAN();
void create_for_SCAN();
void print_for_SCAN();
int cleared(int total[]);

void SCAN()
{
    door=1;
    int ccwise[TOTAL_STATION]={0};
    int wise[TOTAL_STATION]={0};
    int target[TOTAL_STATION]={0};
    int total[TOTAL_STATION*DISTANCE]={0};
    int flag;
    getorder();
    //确定初始方向
    getorder();
    while(order!="end"){
        if(order=="clock"){
            if(door==0){
                action();
                if(flag==bus->position) door=1;
            }
            else{
                total[flag]=0;
                ccwise[flag/DISTANCE+1]=0;
                wise[flag/DISTANCE+1]=0;
                target[flag/DISTANCE+1]=0;
                door=0;
                if(cleared(total)==1) direction=-1;
            }
            print_for_SCAN();
        }
        else{
            create_for_SCAN();
            request_for_SCAN();
        }
        getorder();
    }

}

int cleared(int total[])
{

}