#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int TOTAL_STATION =0;
char * STRATEGY=NULL;
int DISTANCE=0;
int pos=0;//short for position
int tar=0;//short for target
int wise=0;//short for clockwise
int ccwise=0;//short for counterclockwise

void FCFS();
void SSTF();
void SCAN();