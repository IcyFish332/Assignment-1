#include"base.h"
int TOTAL_STATION=0;
int DISTANCE=0;
string STRATEGY="";
int direction;
extern int pos;
int main()
{
    config();
    if(STRATEGY=="FCFS") FCFS();
    if(STRATEGY=="SSTF") SSTF();
    if(STRATEGY=="SCAN") SCAN();
}
