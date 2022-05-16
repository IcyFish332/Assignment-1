#include"base.h"

int request_for_SCAN(int * total);
void create_for_SCAN(int *target,int * wise,int * ccwise,int *total);
void print_for_SCAN(int *target,int * wise,int * ccwise);
int ruler(int flag);
int findmin(int * total);

void SCAN()
{
    door=0;
    int flag;
    int * ccwise=new int [TOTAL_STATION];
    int * wise=new int [TOTAL_STATION];
    int * target=new int [TOTAL_STATION];
    int * total=new int [TOTAL_STATION*DISTANCE];
    bus=creatroutine();

    print_for_SCAN(target,wise,ccwise);
    getorder();
    while(order=="clock"){
        print_for_SCAN(target,wise,ccwise);
        getorder();
    }
    while(order!="clock"){
        create_for_SCAN(target,wise,ccwise,total);
        getorder();
    }
    flag= findmin(total);
    action();
    print_for_SCAN(target,wise,ccwise);
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
            print_for_SCAN(target,wise,ccwise);
        }
        else{
            create_for_SCAN(target,wise,ccwise,total);
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

void create_for_SCAN(int *target,int * wise,int * ccwise,int * total)
{
    char * temp= new char[order.size()+1];
    char * token;
    char * number;
    int num;
    strcpy(temp,order.c_str());
    token=strtok(temp," ");
    number=strtok(NULL," ");
    num=atoi(number);
    if(strcmp(token, "target") == 0)  target[num-1]=1;
    if(strcmp(token, "clockwise") == 0)  wise[num-1]=1;
    if(strcmp(token, "counterclockwise") == 0)  ccwise[num-1]=1;
    total[(num-1)*DISTANCE]=1;
    delete []temp;
}

void print_for_SCAN(int *target,int * wise,int * ccwise)
{
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

int ruler(int flag)
{
    if(flag>bus->position){
        if(direction==0) return flag-bus->position;
        if(direction==1) return TOTAL_STATION*DISTANCE-flag+bus->position;
    }
    if(flag<bus->position){
        if(direction==0) return TOTAL_STATION*DISTANCE+flag-bus->position;
        if(direction==1) return bus->position-flag;
    }
    if(flag==bus->position) return 0;
}

int findmin(int * total)
{
    int min0,min1,flag0,flag1;
    min0=min1=100;
    direction=0;
    for(int i=0;i<TOTAL_STATION*DISTANCE;i++){
        if(total[i]==1){
            if(ruler(i)<min0&&ruler(i)>0){
                min0=ruler(i);
                flag0=i;
            }
        }
    }
    direction=1;
    for(int i=0;i<TOTAL_STATION*DISTANCE;i++){
        if(total[i]==1){
            if(ruler(i)<min1&&ruler(i)>0){
                min1=ruler(i);
                flag1=i;
            }
        }
    }
    if(min0<=min1) {
        direction=0;
        return flag0;
    }
    else {
        direction=1;
        return flag1;
    }
}