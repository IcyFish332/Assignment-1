#include"base.h"
int TOTAL_STATION=0;
int DISTANCE=0;
string STRATEGY="";
int direction;
string order="";
int door;
ROAD * bus;
int TIME=0;
int main()
{
    config();
    if(STRATEGY=="FCFS") FCFS();
    if(STRATEGY=="SSTF") SSTF();
    if(STRATEGY=="SCAN") SCAN();
}
