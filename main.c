#include "base.h"

int main()
{
    FILE *p=fopen("dict.dic","r");
    char buffer[1024];
    char * line;
    char * token;
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
