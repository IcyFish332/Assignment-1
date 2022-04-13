#include"base.h"
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
                STRATEGY=malloc(strlen(token)+1);
                strcpy(STRATEGY,token);
                STRATEGY[4]='\0';
            }
        }
    }
    fclose(p);
    if(TOTAL_STATION==0) TOTAL_STATION=5;
    if(DISTANCE==0) DISTANCE=2;
    if(STRATEGY==NULL) STRATEGY="FCFS";
    cout<< TOTAL_STATION <<endl;
    /*if(!strcmp(token,"FCFS")) FCFS();
    if(!strcmp(token,"SSTF")) SSTF();
    if(!strcmp(token,"SCAN")) SCAN();*/
}
