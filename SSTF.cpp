#include"base.h"

void print_for_SSTF(int *target,int * wise,int * ccwise);
void creat_for_SSTF(int *target,int * wise,int * ccwise,int * total);
void findscan(int *total,int * targerstations,int *target,int * wise,int * ccwise);
int findmin1(int* total);
int ruler1(int flag);
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
    print_for_SSTF(target,wise,ccwise);
    getorder();
    while(order=="clock")
    {
        print_for_SSTF(target,wise,ccwise);
        getorder();
    }
    while(order!="clock")
    {
        creat_for_SSTF(target,wise,ccwise,total);
        getorder();
    }
    main_task=findmin1(total);
    action();
    door=0;
    print_for_SSTF(target,wise,ccwise);
    getorder();
    while(order!="end")
    {
        if(order=="clock")
        {
            if(door==0 && main_task!=-1)
            {
                action();
                if(targetstations[bus->position]==1)    door=1;
                if((main_task-1)*DISTANCE==bus->position)
                {
                    door=1;
                }
            }
            else if(door==1)
            {
                total[bus->position]=0;
                targetstations[bus->position]=0;
                ccwise[bus->position/DISTANCE]=0;
                wise[bus->position/DISTANCE]=0;
                target[bus->position/DISTANCE]=0;
                print_for_SSTF(target,wise,ccwise);
                getorder();
                if(order=="end") break;
                while(order!="clock")
                {
                    creat_for_SSTF(target,wise,ccwise,total);
                    getorder();
                }
                main_task=findmin1(total);
                if(main_task!=-1)
                {
                    action();
                }
                door=0;
                if(targetstations[bus->position]==1)    door=1;
                if((main_task-1)*DISTANCE==bus->position)
                {
                    door=1;
                }
            }
            print_for_SSTF(target,wise,ccwise);
        }
        else
        {

            creat_for_SSTF(target,wise,ccwise,total);
            findscan(total,targetstations,target,wise,ccwise);
            if(main_task==-1)
            {
                main_task=findmin1(total);
            }
        }

        getorder();
    }
    cout<<"end"<<endl;
    FreeMemory(bus);

}

void print_for_SSTF(int *target,int * wise,int * ccwise)
{
    cout<<"TIME:"<<TIME++<<endl;
    cout<<"BUS:"<<endl;
    cout<<"position:"<<bus->position<<endl;
    cout<<"target: ";
    for(int i=0;i<TOTAL_STATION;i++)
        cout<< target[i];
    cout<<endl<<"STATION:"<<endl<<"clockwise: ";
    for(int i=0;i<TOTAL_STATION;i++)
        cout<< wise[i];
    cout<<endl<<"counterclockwise: ";
    for(int i=0;i<TOTAL_STATION;i++)
        cout<< ccwise[i];
    cout<<endl;
}

void creat_for_SSTF(int *target,int * wise,int * ccwise,int * total) {
    int num;
    cin >> num;
    if (order == "target") target[num - 1] = 1;
    if (order == "clockwise") wise[num - 1] = 1;
    if (order == "counterclockwise") ccwise[num - 1] = 1;
    total[(num - 1) * DISTANCE] = 1;
}

void findscan(int *total,int * targerstations,int *target,int * wise,int * ccwise)
{
    int main_distance=ruler1((main_task-1)*DISTANCE);
    int a;
    if(direction==0){
        for(a=0;a<TOTAL_STATION;a++){
            if(wise[a]==1&& main_distance>ruler1(a*DISTANCE)) targerstations[a*DISTANCE]=1;
        }
    }
    else{
        for(a=0;a<TOTAL_STATION;a++){
            if(ccwise[a]==1&& main_distance>ruler1(a*DISTANCE)) targerstations[a*DISTANCE]=1;
        }
    }
    for(a=0;a<TOTAL_STATION;a++){
        if(target[a]==1&& main_distance>ruler1(a*DISTANCE)) targerstations[a*DISTANCE]=1;
    }
}

int findmin1(int * total)
{
    int min0,min1,flag0,flag1;
    min0=min1=100;
    direction=0;
    for(int i=0;i<TOTAL_STATION*DISTANCE;i++)
    {
        if(total[i]==1){
            if(ruler1(i)<min0&&ruler1(i)>0)
            {
                min0=ruler1(i);
                flag0=i;
            }
        }
    }
    direction=1;
    for(int i=0;i<TOTAL_STATION*DISTANCE;i++)
    {
        if(total[i]==1){
            if(ruler1(i)<min1&&ruler1(i)>0)
            {
                min1=ruler1(i);
                flag1=i;
            }
        }
    }
    if(min0==100)
        return -1;
    else
    {
        if(min0<=min1)
        {
            direction=0;
            flag0=(flag0/DISTANCE)+1;
            return flag0;
        }
        else
        {
            direction=1;
            flag1=(flag1/DISTANCE)+1;
            return flag1;
        }
    }
}

int ruler1(int flag)
{
    if(flag>bus->position)
    {
        if(direction==0) return flag-bus->position;
        if(direction==1) return TOTAL_STATION*DISTANCE-flag+bus->position;
    }
    if(flag<bus->position)
    {
        if(direction==0) return TOTAL_STATION*DISTANCE+flag-bus->position;
        if(direction==1) return bus->position-flag;
    }
    if(flag==bus->position) return 0;
}