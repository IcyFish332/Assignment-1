#include"base.h"

int request_for_SCAN(int * total);

void SCAN()
{
    int flag;
    int * ccwise=new int [TOTAL_STATION];
    int * wise=new int [TOTAL_STATION];
    int * target=new int [TOTAL_STATION];
    int * total=new int [TOTAL_STATION*DISTANCE];

    for(int i=0;i<TOTAL_STATION;i++)
    {
        ccwise[i]=0;
        wise[i]=0;
        target[i]=0;
    }
    for (int i=0;i<TOTAL_STATION*DISTANCE;i++)
        total[i]=0;
    bus=creatroutine();
    door=0;

    print(target,wise,ccwise);
    getorder();
    while(order=="clock"){
        print(target,wise,ccwise);
        getorder();
    }
    while(order!="clock"){
        create(target,wise,ccwise,total);
        getorder();
    }
    flag= findmin(total);
    action();
    print(target,wise,ccwise);
    getorder();
    while(order!="end"){
        if(order=="clock"){
            if(door==0&&flag!=-1){
                action();
                if(flag==bus->position) door=1;
            }
            else{
                total[bus->position]=0;
                ccwise[bus->position/DISTANCE]=0;
                wise[bus->position/DISTANCE]=0;
                target[bus->position/DISTANCE]=0;
                door=0;
                flag=request_for_SCAN(total);
            }
            print(target,wise,ccwise);
        }
        else{
            create(target,wise,ccwise,total);
            flag=request_for_SCAN(total);
        }
        getorder();
    }
    cout<<"end"<<endl;

    delete []ccwise;
    delete []wise;
    delete []target;
    delete []total;
    FreeMemory(bus);
}

int request_for_SCAN(int * total)
{
    int flag;
    int min=100;
    for(int i=0;i<TOTAL_STATION*DISTANCE;i++){
        if(total[i]==1){
            if(ruler(i)<min&&ruler(i)>0) {
                min=ruler(i);
                flag=i;
            }
        }
    }
    if(min==100) return -1;
    if(min>TOTAL_STATION*DISTANCE*0.5) direction=(direction+1)%2;
    return flag;
}