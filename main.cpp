#include"base.h"
using namespace std;
int TOTAL_STATION =0;
string STRATEGY="";
int DISTANCE=0;
int pos=0;//short for position
//int tar=0;//short for target
//int wise[10];//short for clockwise
//int ccwise[10];//short for counterclockwise
//int time=0;

int main()
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
    FCFS();
    SSTF();
    SCAN();
}
