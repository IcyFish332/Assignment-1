#include"base.h"

void request_for_SCAN(int * total);
void create_for_SCAN(int *target,int * wise,int * ccwise,int *total);
void print_for_SCAN(int *target,int * wise,int * ccwise);
int cleared(int * total);
int ruler(int flag);

void SCAN()
{
    door=0;
    int flag;
    int * ccwise=new int [TOTAL_STATION];
    int * wise=new int [TOTAL_STATION];
    int * target=new int [TOTAL_STATION];
    int * total=new int [TOTAL_STATION*DISTANCE];

    /*cout<< bus->position << endl;
    direction=0;
    bus=bus->wise;
    cout<< bus->position << endl;*/ //测试代码

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
    direction=0;
    request_for_SCAN(total);
    action();
    print_for_SCAN(target,wise,ccwise);
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
            print_for_SCAN(target,wise,ccwise);
        }
        else{
            create_for_SCAN(target,wise,ccwise,total);
            request_for_SCAN(total);
        }
        getorder();
    }
    cout<<"end"<<endl;

    delete []ccwise;
    delete []wise;
    delete []target;
    delete []total;
}

void request_for_SCAN(int * total)
{
    int min=100;
    for(int i=0;i<TOTAL_STATION*DISTANCE;i++){
        if(total[i]==1){
            if(ruler(i)<min) min=ruler(i);
        }
    }
    if(min>TOTAL_STATION*DISTANCE*0.5) direction=(direction+1)%2;
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

int cleared(int * total)
{
    for(int i=0;i< TOTAL_STATION;i++){
        if(total[i]==1) return 0;
    }
    return 1;
}

int ruler(int flag)
{
    if((flag-1)*DISTANCE>bus->position){
        if(direction==0) return (flag-1)*DISTANCE-bus->position;
        if(direction==1) return TOTAL_STATION*DISTANCE-(flag-1)*DISTANCE+bus->position;
    }
    if((flag-1)*DISTANCE<bus->position){
        if(direction==0) return bus->position-(flag-1)*DISTANCE;
        if(direction==1) return TOTAL_STATION*DISTANCE+(flag-1)*DISTANCE-bus->position;
    }
}