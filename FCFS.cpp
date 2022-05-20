#include"base.h"

typedef struct list
{
    int* ccwise=new int[TOTAL_STATION];
    int* wise=new int[TOTAL_STATION];
    int* target=new int[TOTAL_STATION];
    struct list* next;
}Task;

Task* recording=new Task;
Task* last=NULL;
Task* head_for_FCFS=NULL;
Task* doing=NULL;//指向当前所作的任务

void print_for_FCFS(Task* recording);
void create_for_FCFS();
void request_for_FCFS();

void FCFS()
{
    //将recording中所有数组初始化为0
    int i;
    int station;
    for(i=0;i<TOTAL_STATION;i++)
    {
        recording->ccwise[i]=0;
        recording->wise[i]=0;
        recording->target[i]=0;
    }
    
    bus=creatroutine();

    print_for_FCFS(recording);//先打印一次，此时recording为0，故打印的也都是0
    getorder();
    while(order!="end")
    {
        if(order!="clock")
        {
            create_for_FCFS();
        }
        request_for_FCFS();
        if(order=="clock")
        {
            action();
            station=bus->station;
            print_for_FCFS(recording);
            if(doing!=NULL&&station!=-1)//当前有任务，且走到了站点再进行判断是否到达任务地点
            {
                //若到达任务地点，即如果当前执行任务的wise，ccwise或target的任意一个数组的第【station-1】位为1
                if((doing->wise[station-1]==1)||(doing->ccwise[station-1]==1)||(doing->target[station-1]==1))
                {
                    door=1;//开门
                    //recording中所有数组相应位置减去doing的相应位置，即删掉任务
                    recording->wise[station-1]=recording->wise[station-1]-doing->wise[station-1];
                    recording->ccwise[station-1]=recording->ccwise[station-1]-doing->ccwise[station-1];
                    recording->target[station-1]=recording->target[station-1]-doing->target[station-1];
                    //当存在下一个任务且下一个任务相同
                    while((doing->next!=NULL)&&((doing->next->wise[station-1]==1)||(doing->next->ccwise[station-1]==1)||(doing->next->target[station-1]==1)))
                    {
                        doing=doing->next;//任务指针向后移一个
                        //recording减去已完成的任务
                        recording->wise[station-1]=recording->wise[station-1]-doing->wise[station-1];
                        recording->ccwise[station-1]=recording->ccwise[station-1]-doing->ccwise[station-1];
                        recording->target[station-1]=recording->target[station-1]-doing->target[station-1];
                    }
            
                    getorder();
                    while(order!="clock")
                    {
                        create_for_FCFS();
                        //同上，这时不用加doing next不为null条件是因为 按顺序完成请求，如果这时候doing next又相同了，那只可能是
                        //刚刚getorder进来的，即此为最后一个任务
                        if((doing->next->wise[station-1]==1)||(doing->next->ccwise[station-1]==1)||(doing->next->target[station-1]==1))
                        {
                            doing=doing->next;
                            recording->wise[station-1]=recording->wise[station-1]-doing->wise[station-1];
                            recording->ccwise[station-1]=recording->ccwise[station-1]-doing->ccwise[station-1];
                            recording->target[station-1]=recording->target[station-1]-doing->target[station-1];
                        }
                        getorder();
                    }
                    //当getorder为clock时跳出循环
                    print_for_FCFS(recording);
                    door=0;//关门
                    doing=doing->next;//任务完成，任务指针向后移一位
                }
            }
        }

    getorder();
    }
    FreeMemory(bus);
    //cout<<"FCFS:I am here!"<<endl;
}

void create_for_FCFS()
{
    int num;
    cin>>num;
    int i;
    
    int check=0;//check为0时创建链表
    
    
    //若请求为当前未完成的一模一样的任务，则不创建链表
    if(order=="clockwise")
    {
        if(recording->wise[num-1]>=1)
        {
            check=1;
        }
    }
    else if(order=="counterclockwise")
    {
        if(recording->ccwise[num-1]>=1)
        {
            check=1;
        }
    }
    else if(order=="target")
    {
        if(recording->target[num-1]>=1)
        {
            check=1;
        }
    }
    if(check==0)
    {
        Task *current=new Task;
        current->next=NULL;
        if(order=="clockwise")
        {
            current->wise[num-1]=1;
           
            for(i=0;i<TOTAL_STATION;i++)
            {
                current->ccwise[i]=0;
               
                current->target[i]=0;
            }
            recording->wise[num-1]+=1;
        }
        if(order=="counterclockwise")
        {
            current->ccwise[num-1]=1;
            for(i=0;i<TOTAL_STATION;i++)
            {
                
                current->wise[i]=0;
                current->target[i]=0;
            }
            recording->ccwise[num-1]+=1;
        }
        if(order=="target")
        {
            current->target[num-1]=1;
            for(i=0;i<TOTAL_STATION;i++)
            {
                current->ccwise[i]=0;
                current->wise[i]=0;
            }
            recording->target[num-1]+=1;
        }
        if(doing==NULL)
        {
            doing=current;
        }
        if(head_for_FCFS==NULL)
        {
            head_for_FCFS=current;
            last=current;
            doing=current;
        }
        else
        {
            last->next=current;
            last=last->next;
        }
    }  
}
void request_for_FCFS()
{
    int i;
    int num;//表示目标站点
    if(doing==NULL)
    {
        direction=-1;//没任务则不动
    }
    else
    {
        for(i=0;i<TOTAL_STATION;i++)
        {
            if(doing->wise[i]==1)
            {
                num=i+1;
            }
            else if(doing->ccwise[i]==1)
            {
                num=i+1;
            }
            else if(doing->target[i]==1)
            {
                num=i+1;
            }
        }//((num-1)*DISTANCE)为目标站点所在的position
        if((((num-1)*DISTANCE)-bus->position>0&&((num-1)*DISTANCE)-bus->position<=(TOTAL_STATION*DISTANCE)*0.5)||(((num-1)*DISTANCE)-bus->position<0&&bus->position-((num-1)*DISTANCE)>=(TOTAL_STATION*DISTANCE)*0.5))
        {
            direction=0;//顺时针
        }
        else if(((num-1)*DISTANCE)-bus->position==0)//当目标站点就是现在所处的位置，则不动
        {
            direction=-1;//不动
        }
        else
        {
            direction=1;//逆时针
        }
    }
   
}

void print_for_FCFS(Task* recording)
{
    int i=0;
    cout<<"TIME: "<<TIME++<<endl;
    cout<<"BUS:"<<endl;
    cout<<"position: "<<bus->position<<endl;
    cout<<"target: ";
    for(i=0;i<TOTAL_STATION;i++)
    {
        if(recording->target[i]>=1)
        {
            cout<<"1";
        }
        else
        {
            cout<<"0";
        }
        
    }
    cout<<endl<<"STATION: "<<endl<<"clockwise: ";
    for(i=0;i<TOTAL_STATION;i++)
    {
        if(recording->wise[i]>=1)
        {
            cout<<"1";
        }
        else
        {
            cout<<"0";
        }
    }
    cout<<endl<<"counterclockwise: ";
    for(i=0;i<TOTAL_STATION;i++)
    {
        if(recording->ccwise[i]>=1)
        {
            cout<<"1";
        }
        else
        {
            cout<<"0";
        }
    }
    cout<<endl;
}