#include"base.h"

void config()
{
    FILE *p=fopen("dict.dic","r");
    char buffer[1024];
    char * line;
    char * token;
    char * tmp;
    while((line = fgets(buffer, sizeof(buffer), p))!=NULL){
        if(buffer[0]!='#'){
            token=strtok(line," ");
            if(!strcmp(token,"TOTAL_STATION")){
                token=strtok(NULL," ");
                token=strtok(NULL," ");
                TOTAL_STATION=atoi(token);
            }
            else if(!strcmp(token,"DISTANCE")){
                token=strtok(NULL," ");
                token=strtok(NULL," ");
                DISTANCE=atoi(token);
            }
            else if(!strcmp(token,"STRATEGY")){
                token=strtok(NULL," ");
                token=strtok(NULL," ");
                tmp=(char *)malloc(strlen(token)+1);
                strcpy(tmp,token);
                tmp[4]='\0';
                STRATEGY=tmp;
                free(tmp);
            }
        }
    }
    fclose(p);
    if(TOTAL_STATION==0) TOTAL_STATION=5;
    if(DISTANCE==0) DISTANCE=2;
    if(STRATEGY=="") STRATEGY="FCFS";
}

ROAD * creatroutine()
{
    int pos;
    ROAD * head=new node;
    head->position=0;
    head->station=1;
    head->ccwise=NULL;
    head->wise=NULL;
    ROAD* tmp=head;
    for(pos=1;pos<DISTANCE*TOTAL_STATION;pos++)
    {
        tmp=appendNode(tmp,pos);
    }
    tmp->wise=head;
    head->ccwise=tmp;
    return head;
}

ROAD* appendNode(ROAD* head, int pos)
{
    ROAD* newnode=new ROAD;
    if(newnode!=NULL)
    {
        newnode->position=pos;
        if(pos%DISTANCE==0)
        {
            newnode->station=(pos/DISTANCE)+1;
        }
        else newnode->station=-1;
        newnode->ccwise=head;
        newnode->wise=NULL;
        head->wise=newnode;
        return newnode;
    }
}

void getorder()
{
    cin >> order;
}

void action()
{
    if(direction==0)//顺时针
    {
        bus=bus->wise;
    } 
    else if(direction==1)//逆时针
    {
        bus=bus->ccwise;
    }
}

void FreeMemory(ROAD* head)
{
    ROAD* p=NULL;
    while(head!=NULL)
    {
        p=head->wise->wise;
        if (head->wise==head)
        {
            delete head;
            head=NULL;
        }
        else
        {
            delete (head->wise);
            head->wise=p;
            p->ccwise=head;
        }
    }
}

void create(int *target,int * wise,int * ccwise,int * total)
{
    int num;
    cin >>num;
    if(order=="target")  target[num-1]=1;
    if(order=="clockwise")  wise[num-1]=1;
    if(order=="counterclockwise")  ccwise[num-1]=1;
    total[(num-1)*DISTANCE]=1;
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
    for(int i=0;i<TOTAL_STATION*DISTANCE;i++)
    {
        if(total[i]==1){
            if(ruler(i)<min0 && ruler(i)>0)
            {
                min0=ruler(i);
                flag0=i;
            }
        }
    }
    direction=1;
    for(int i=0;i<TOTAL_STATION*DISTANCE;i++)
    {
        if(total[i]==1){
            if(ruler(i)<min1 && ruler(i)>0)
            {
                min1=ruler(i);
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


void print(int *target,int * wise,int * ccwise)
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