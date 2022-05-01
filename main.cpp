#include"base.h"
int TOTAL_STATION=0;
int DISTANCE=0;
string STRATEGY="";
int direction;
int pos;
string order="";
ROAD * head=creatroutine();
ROAD * bus=head;

int main()
{
    config();
    if(STRATEGY=="FCFS") FCFS();
    if(STRATEGY=="SSTF") SSTF();
    if(STRATEGY=="SCAN") SCAN();
}
