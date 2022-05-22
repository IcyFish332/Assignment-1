#include"base.h"

void findscan(int * targerstations,int *target,int * wise,int * ccwise);
int main_task=-1;

void SSTF()
{
    int* ccwise=new int [TOTAL_STATION];
    int* wise=new int [TOTAL_STATION];
    int* target=new int [TOTAL_STATION];
    int* total=new int [TOTAL_STATION*DISTANCE];
    int* targetstations=new int [TOTAL_STATION*DISTANCE];

    for(int i=0;i<TOTAL_STATION;i++)
    {
        ccwise[i]=0;
        wise[i]=0;
        target[i]=0;
    }
    for (int i=0;i<TOTAL_STATION*DISTANCE;i++)
    {
        total[i]=0;
        targetstations[i]=0;
    }
    bus=creatroutine();
    door=0;

    print(target,wise,ccwise);
    getorder();
    while(order=="clock")
    {
        print(target,wise,ccwise);
        getorder();
    }
    while(order!="clock")
    {
        create(target,wise,ccwise,total);
        getorder();
    }
    main_task=findmin(total);
    action();
    door=0;
    print(target,wise,ccwise);
    getorder();
    while(order!="end")
    {
        if(order=="clock")
        {
            if(door==0 && main_task!=-1)
            {
                action();
                if(targetstations[bus->position]==1)    door=1;
                if((main_task-1)*DISTANCE==bus->position) door=1;
            }
            else if(door==1)
            {
                total[bus->position]=0;
                targetstations[bus->position]=0;
                ccwise[bus->position/DISTANCE]=0;
                wise[bus->position/DISTANCE]=0;
                target[bus->position/DISTANCE]=0;
                print(target,wise,ccwise);
                getorder();
                if(order=="end") break;
                while(order!="clock")
                {
                    create(target,wise,ccwise,total);
                    getorder();
                }
                main_task=findmin(total);
                if(main_task!=-1) action();
                door=0;
                if(targetstations[bus->position]==1)    door=1;
                if((main_task-1)*DISTANCE==bus->position) door=1;
            }
            print(target,wise,ccwise);
        }
        else
        {

            create(target,wise,ccwise,total);
            if(main_task==-1) main_task=findmin(total);
            findscan(targetstations,target,wise,ccwise);
        }
        getorder();
    }
    cout<<"end"<<endl;

    delete []ccwise;
    delete []wise;
    delete []target;
    delete []total;
    delete []targetstations;
    FreeMemory(bus);
}

void findscan(int * targerstations,int *target,int * wise,int * ccwise)
{
    int main_distance=ruler((main_task-1)*DISTANCE);
    int a;
    if(direction==0){
        for(a=0;a<TOTAL_STATION;a++){
            if(wise[a]==1&& main_distance>ruler(a*DISTANCE)) targerstations[a*DISTANCE]=1;
        }
    }
    else{
        for(a=0;a<TOTAL_STATION;a++){
            if(ccwise[a]==1&& main_distance>ruler(a*DISTANCE)) targerstations[a*DISTANCE]=1;
        }
    }
    for(a=0;a<TOTAL_STATION;a++){
        if(target[a]==1&& main_distance>ruler(a*DISTANCE)) targerstations[a*DISTANCE]=1;
    }
}