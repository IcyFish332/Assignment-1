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