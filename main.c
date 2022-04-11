#include "base.h"

int main()
{
    FILE *p=fopen("dict.dic","r");
    char buffer[1024];
    char * token;
    while(p!=EOF){
        fscanf(p,"%s",buffer);
        if(buffer[0]!='#'){
            token=strtok(buffer," ");
            if(token=="TOTAL_STATION"){
                token=strtok(NULL," ");
                token=strtok(NULL," ");
                TOTAL_STATION=atoi(token);
            }
            else if(token=="DISTANCE"){
                token=strtok(NULL," ");
                token=strtok(NULL," ");
                DISTANCE=atoi(token);
            }
            else if(token=="STRATEGY"){
                token=strtok(NULL," ");
                token=strtok(NULL," ");
                STRATEGY=token;
            }
        }
    }
    fclose(p);
    if(TOTAL_STATION==0) TOTAL_STATION=5;
    if(DISTANCE==0) DISTANCE=2;
    if(STRATEGY==NULL) STRATEGY="FCFS";
    printf("%d %d %s\n",TOTAL_STATION,DISTANCE,STRATEGY);
}
