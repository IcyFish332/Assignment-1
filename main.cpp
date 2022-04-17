#include"base.h"
int main()
{
    config();
    if(STRATEGY=="FCFS") FCFS();
    if(STRATEGY=="SSTF") SSTF();
    if(STRATEGY=="SCAN") SCAN();
}
