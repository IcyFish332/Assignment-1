# 自动驾驶公交车调度系统

## 问题描述

用程序模拟一个城市自动驾驶公交车调度系统。自动驾驶公交车调度系统，系统中的要素如下示意图：

![Untitled](https://user-images.githubusercontent.com/91677266/169697449-95010b79-ec75-4276-a4a2-8f8b2788e178.png)

图一：简单的系统示意图

---

## 基本规则

- 规则1：有一个闭环的公交轨道，公交车只能在轨道上运行。轨道的位置由像素坐标表示，长度以像素个数为单位计算。
- 规则2：公交车运行方向分顺时针、逆时针两种方向，根据调度策略可切换方向。
- 规则3：轨道内预先设置乘车站N个，车站的位置由像素坐标表示，车站距离不相等。
- 规则4：由程序接收动态发出（读文件或键盘、鼠标操作）的乘车请求，动态刷新显示“等待请求数”指标；然后根据请求车站情况，更新车站的状态：没有乘车请求的车站显示为蓝色，有乘车请求的车站显示为红色（要能表示两个方向的请求）。
- 规则5：一辆车的载客数不限，可以接收所经过的所有乘车站请求。车辆的车速保持匀速不变，都设置为1 S，车速以每秒多少像素表示。
- 规则6：程序初始，默认一辆公交车从轨道的左上角发车，根据调度策略确定行驶方向，按设定车速S行驶（定时刷新显示公交车的当前位置和“时间”显示，时间以秒为单位），途经有乘车请求的车站时停车P秒，完成本站的所有请求，刷新显示“已完成请求数”和“最大等待时间”指标。
- 规则7：由程序接收动态发出（读文件或键盘、鼠标操作）的“停运”指令，收到停运指令后，程序不再接收新的乘车请求（准备收车状态），但需要将已有乘车请求处理完，然后更新“已完成请求数”和“最大等待时间”指标，程序退出。
- 规则8：最大等待时间的计算方法，每个乘车请求发出后，直到公交车经过请求车站完成服务的时间间隔，以秒为单位，取所有乘车请求完成时间的最大值。

---

## 需求分析

### 基本说明

- 环形轨道，一辆车，车辆可以双向任意行驶。我们规定车辆的原始位置为0（该位置也是车站1的位置），按顺时针方向每个单位位置坐标加1。

> 如果轨道总长为10，则按顺时针方向走，位置9的下一个为位置0。车站编号同理，也是按顺时针方向依次递增。
> 
- 车速固定，每秒一个单位。**停车接人**或**乘客下车**时需要停车一秒钟。**无论一次停站完成几个服务停留时间统一为1秒钟**。
- 各站之间距离相等，车辆经过站点时，根据调度策略，车辆可以停也可以不停。其他位置不允许停车。车辆只能在站点停站时才能改变行驶方向。
- 各站之间距离可配置，站点个数可配置，调度策略可配置。这三个参数保存在配置文件中，程序要通过读配置文件获取。

> 配置文件的名字为dict.dic。 配置文件为文本文件，以#号开头的行是注释。 每行一个参数，
格式为：参数 = 值的形式。
> 

其中参数有三个:`TOTAL_STATION`，代表站点总数，为大于1且小于等于10的整数；`DISTANCE`，代表每站之间的距离，为大于0且小于6的整数；`STRATEGY`，代表调度策略，只能是`FCFS`（先来先服务），`SSTF`（最短寻找时间优先）和 `SCAN`（顺便服务）之一。

> 另外:
> 
> 1. 如果某个参数没有出现在配置文件中，则该参数取缺省值。
> 
> 三个参数的缺省值如下：
> 
> ```c
> TOTAL_STATION = 5
> STRATEGY = FCFS
> DISTANCE = 2
> ```
> 
> 1. 三个参数在文件中的顺序没有规定。
> 2. 显然，`TOTAL_STATION`与`DISTANCE`乘积就是**轨道总长度**，所以配置文件中没有这个参数。

### 策略说明

### 先来先服务策略（FCFS）

**将所有乘车请求按发出时间排队，然后按队列顺序逐一完成**

> 先来先服务是一种随即服务算法，是一种最简单的电梯调度算法。它根据乘客请求乘坐电梯的先后次序进行调度。此算法的优点是公平、简单，且每个乘客的请求都能依次地得到处理，不会出现某一乘客的请求长期得不到满足的情况。这种方法在载荷较轻松的时，性能尚可接受，在载荷较大的情况下，这种算法的性能就会严重下降，甚至恶化人们之所以研究这种在载荷较大的情况下几乎不可用的算法，有两个原因：
> 
> 
> > 任何调度算法在请求队列长度为1时，请求速率极低或相邻请求的间隔为无穷大时使用先来先服务算法既对调度效率不会产生影响，而且实现这种算法极其简单。先来先服务算法可以作为衡量其他算法的标准。
> > 

### 最短寻找时间优先（SSTF）

**寻找可最快到达车站**

> 最短寻找时间优先策略选择下一个服务对象的原则是最短寻找时间。这样乘车请求队列中距当前公交车位置能够最先到达的车站请求信号就是下一个服务对象。注意计算最短寻找时间时，要在当前方向和反方向两个方向去计算，然后找出最短的行驶方向和到达时间。在重载荷的情况下，最短寻找时间优先算法的平均响应时间较短，但响应时间的方差较大，原因是队列中的某些请求可能长时间得不到响应，出现所谓的“饿死”现象。
> 

### 顺便服务策略（SCAN）

**（1）按小车当前位置和当前行驶方向，计算所有等待乘车请求的预计完成时间，找出最短完成时间的车站，作为当前目标进行调度。（2）若按规则（1）找出的最短完成时间超过跑完轨道一半距离时间时，应该切换行驶方向。然后重新按规则1找出最短完成时间的车站，作为当前目标进行调度。**

> 顺便服务策略是一种按照车站顺序依次服务请求策略，它让公交车方向较稳定地往返运行，在运行过程中优先响应在当前运行方向的最快到达车站请求。避免了公交车频繁的切换行驶方向。顺便服务策略的平均响应时间比最短寻找时间优先算法长，但是响应时间方差比最短寻找时间优先算法小，从统计学角度来讲，顺便服务策略要比最短寻找时间优先算法稳定。
> 

### 策略补充说明：

1. 每一个请求均为单独的服务，就是说**车内请求与站台请求没有必然联系**；
2. 当车**完成服务时要选择路程短的方向行驶**，如果两个方向路程相同则选择**顺时针方向**；
3. 如果在某个请求**没有完成时**再有**相同的请求发生**，则该请求被**抛弃**。如果**已完成的请求再次发生**时应按**新请求**处理。
4. 对于*先来先服务策略*，车一次停站只完成一个请求，即使在这个站点上即有乘车请求，车内也有到该站的请求也只能按算法完成其中的一个。但是如果下一个请求恰好在同一站点，则可以一次停站完成2个或2个以上的请求。也就是说只停1秒完成多个请求。
5. 对于最短寻找时间优先策略，一次服务的请求（目标）一旦确定，即使中途产生更优的请求也不可以更改。但如果新的请求恰好可以顺便服务（同方向的站台请求或车内请求），可以为新的请求停站。当车到达目标地点时，该站点恰好有两个相反的请求，可以停一次车完成这2个服务。
6. 程序计算离当前车的位置最近的`target`、`counterclockwise`、`clockwise`请求，如果**都没有请求则原地不动**，否则**按最近的路线（顺、逆时针）去接（送）**，如果车途中遇到与车目前**同方向的上车请求或下车请求**可以停下一秒解决【**请求至少在车到请求地前一个clock提出**，到达该请求地时再提出请求的忽略】，**反方向的上车请求忽略**，车接到人（送完人）后，反复此过程，直到end
7. 对于顺便服务策略，第一次行驶方向由第一个请求出现后1秒钟内全部请求中时间最短的那个请求决定。在行使过程中，如果所有的请求按照当前的行驶方向找出的最短完成时间都超过跑完轨道一半距离时间时，应该切换行驶方向。这是唯一的一个切换方向的规则。车辆行驶过程中如果经过的站点有服务请求，则不管这个请求的类型一律停站，并认为此请求完成。这意味着一次停车可能完成3个服务。
8. 对于*后两种策略*，如果车辆在某站点本没有停车计划，新的请求要至少要提前1秒钟产生才能享受顺便服务。也就是说不为太近的请求停车。

---

# 概要设计

## 1.1 输入输出设计

### 核心版本

**输入说明**

若干行，每行一个指令。
指令共5种。分别为end、clock、counterclockwise、clockwise 和target。

| end | 结束指令 | 只在最后一行出现一次； |
| --- | --- | --- |
| clock | 时钟指令 | 每出现一次代表过了一秒钟； |
| counterclockwise、clockwise、target | 为请求指令 | 同一行内后边有一个整数。 |
| counterclockwise | 表示逆时针方向 | 整数代表请求发生的站点号 |
| clockwise | 代表顺时针方向 | 整数代表请求发生的站点号 |
| target | 车厢内请求 | 整数代表要去的站点号。 |

**输出说明**

程序开始，先输出一次初始状态，然后每个clock输出一次当前状态。每次输出的格式如下：

```
BUS:
position:0
target: 0000000000
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
```

> 其中前三行代表车辆:
> 
> 
> 
> | BUS | 固定不变 | - |
> | --- | --- | --- |
> | position | 固定不变 | 后边的数字代表当前车辆位置 |
> | target | 固定不变 | 后边一排数字依次代表车内站点请求情况，0表示没有请求，1表示有请求。 |
> 
> 后三行代表各站点的状态:
> 
> | STATION | 固定不变 | - |
> | --- | --- | --- |
> | clockwise | 固定不变 | 后边的数字依次代表各站点顺时针方向的请求情况，0表示没有请求，1表示有请求。 |
> | counterclockwise | 固定不变 | 后边的数字依次代表各站点逆时针方向的请求情况，0表示没有请求，1表示有请求。 |

### 动画并发版本

暂无

### 后续改进版本

暂无

## 1.2 算法设计

### 自动机模型

![截屏2022-05-08_21 57 00](https://user-images.githubusercontent.com/91677266/169697550-7d2c3ca2-362a-4333-90e7-791d2e55d579.png)


图二：公交车状态

![截屏2022-05-08_21 58 03](https://user-images.githubusercontent.com/91677266/169697561-4c2a7c26-2922-40bf-875d-0425606856cf.png)


图三：“处理clock”的细化

![截屏2022-05-08_22 02 15](https://user-images.githubusercontent.com/91677266/169697571-b86d0fa7-b79d-47c9-8d02-b579c43531a1.png)


图四：“处理其他任务”的细化（以SSTF为例）

无论使用三种策略中的哪种，公交车的行驶状态均可以用图二表示，只是“处理position、 counterclockwise、 clockwise”的方式不同。而图三、图四是“处理clock”、“处理其他任务”的细化，通过有限状态自动机这一模型可以实现具体算法。

## 1.3 高层数据结构定义

### 1.3.1 常量定义

无

### 1.3.2 全局变量定义

```cpp
int TOTAL_STATION;
string STRATEGY;
int DISTANCE;
int direction;
int door;
int pos;
string order;
int TIME;
extern ROAD * bus;
```

### 1.3.3 数据结构定义

**（1）路线位置的结构**

```cpp
typedef struct node{
    int position;
    int station; //代表站点编号，若为-1表示不是站点
    struct node * ccwise;
    struct node * wise;
}ROAD;
```

**（2）FCFS策略的请求队列结构**

```cpp
typedef struct list
{
   int ccwise[TOTAL_STATION];
   int wise[TOTAL_STATION];
   int target[TOTAL_STATION];
   struct list *next；
}Task；
```

**（3）SSTF策略的请求队列结构**

```cpp
int* ccwise=new int [TOTAL_STATION];
int* wise=new int [TOTAL_STATION];
int* target=new int [TOTAL_STATION];
int* total=new int [TOTAL_STATION*DISTANCE];
int* targetstations=new int [TOTAL_STATION*DISTANCE];
```

**（4）SCAN策略的请求队列结构**

```cpp
int* ccwise=new int [TOTAL_STATION];
int* wise=new int [TOTAL_STATION];
int* target=new int [TOTAL_STATION];
int* total=new int [TOTAL_STATION*DISTANCE];
```

## 1.4 系统模块划分

### **一、软件结构图**

本系统划分为main.cpp、FCFS.cpp、SSTF.cpp、SCAN.cpp、functions.cpp五个模块。各模块功能如下：

**1.模块名称：main.cpp**

模块功能简要描述：主函数，运行配置读取程序以及不同的策略程序

**2.模块名称：FCFS.cpp**

模块功能简要描述：运行FCFS策略

**3.模块名称：SSTF.cpp**

模块功能简要描述：运行SSTF策略

**4.模块名称：SCAN.cpp**

模块功能简要描述：运行SCAN策略

**5.模块名称：functions.cpp**

模块功能简要描述：实现一些细小功能，存放多数公用函数接口

**模块结构图如图所示**

<img width="528" alt="截屏2022-05-02_21 47 40" src="https://user-images.githubusercontent.com/91677266/169697540-3e0693d5-abdf-4475-8bad-df5718e5b35f.png">


### 二、文件及函数组成

| 源文件 | 源文件说明 | 函数名 | 功能 |
| --- | --- | --- | --- |
| FCFS.cpp | 本文件用于运行FCFS策略 | void request_for_FCFS() | 跟据当前任务以及FCFS策略决定行走方向 |
|  |  | void create_for_FCFS() | 创建任务链表 |
|  |  | void print_for_FCFS(Task* recording） | 打印现在的任务及车的位置 |
|  |  | void FCFS（） | 运行FCFS策略 |
| SSTF.cpp | 本文件用于运行SSTF策略 | void findscan(int * targerstations,int *target,int * wise,int * ccwise); | 寻找顺便服务对象 函数可改变targetstations数组 |
|  |  | void SSTF() | 运行SSTF策略 |
| SCAN.cpp | 本文件用于运行SCAN策略 | int request_for_SCAN(int * total） | 跟据当前任务以及SCAN策略决定行走方向 |
|  |  | void SCAN(int * total) | 运行SCAN策略 |
| functions.cpp | 本文件用于实现一些细小功能，存放多数公用函数接口 | ROAD * appendNode(ROAD* head, int pos) | 添加站点节点 |
|  |  | ROAD * creatroutine() | 创建路线链表 |
|  |  | void config() | 读取配置文件数据 |
|  |  | void getorder() | 读取命令 |
|  |  | void action() | 移动车辆 |
|  |  | void FreeMemory(ROAD* head) | 释放路线链表 |
|  |  | void create(int *target,int * wise,int * ccwise,int * total) | 创建任务 |
|  |  | int ruler(int flag) | 测量当前方向下当前位置与目标站点的距离 |
|  |  | int findmin(int * total) | 找到距离最近的站点，并改变方向 |
|  |  | void print(int *target,int * wise,int * ccwise) | 用于SSTF和SCAN策略的打印 |

### 三、函数说明

| 序号 | 函数原型 | 功能 | 参数 | 返回值 |
| --- | --- | --- | --- | --- |
| 1 | void config() | 读取配置文件数据 | void | void |
| 2 | ROAD * creatroutine() | 创建路线链表 | void | 公交路线的起始节点 |
| 3 | ROAD * appendNode(ROAD* head, int pos) | 添加站点节点 | 对应节点 | 输入位置和头节点 |
| 4 | void getorder() | 读取命令 | void | void |
| 5 | void action() | 移动车辆 | void | void |
| 6 | void request_for_FCFS() | 跟据当前任务以及FCFS策略决定行走方向 | void | void |
| 7 | void create_for_FCFS() | 创建任务链表 | void | void |
| 8 | void print_for_FCFS(Task* recording) | 打印现在的任务及车的位置 | 记录任务的节点 | void |
| 9 | void findscan(int* total,int* targerstations,int* target,int*  wise,int* ccwise) | 寻找顺便服务对象，将对象的位置存入targetstations数组 | 总任务数组、三个任务数组、targetstations数组 | void |
| 10 | int request_for_SCAN(int* total） | 跟据当前任务以及SCAN策略决定行走方向 | 所有任务位置的数组指针 | 当前任务位置 |
| 11 | void FreeMemory(ROAD* head) | 释放路线链表 | ROAD | void |
| 12 | void create(int *target,int * wise,int * ccwise,int * total) | 创建任务 | 总任务数组、三个任务数组 | void |
| 13 | int ruler(int flag) | 测量当前方向下当前位置与目标站点的距离 | 站点坐标 | 距离 |
| 14 | int findmin(int * total) | 找到距离最近的站点，并改变方向 | 总任务数组 | 站点坐标 |
| 15 | void print(int *target,int * wise,int * ccwise) | 用于SSTF和SCAN策略的打印 | 三个任务数组 | void |
| 16 | void FCFS() | 运行FCFS策略 | void | void |
| 17 | void SSTF() | 运行SSTF策略 | void | void |
| 18 | void SCAN() | 运行SCAN策略 | void | void |

## 1.5 高层算法设计

**FCFS策略：**

```cpp
while（input不为"end"）//input由getorder获取
{
  if(input不为"clock"）
  {
    create（input）;//创建任务链表
  }
  request();//跟据当前任务决定行走方向
  else if(input为"clock"）
  {
    action（）;//根据方向移动车辆
    打印现在的任务及车的位置。
    if（到达位置）
    {
       门开
       while（下一个任务相同）
       {
          当前执行的任务指针向后移一个
       }
       while（下一个input不是"clock"）
       {
          create（input）//创建任务链表
          while（下一个任务相同）
          {
              当前执行的任务指针向后移一个
          }
       }
        打印现在的任务及车的位置//即clock时打印
        门关
        当前执行的任务指针向后移一个//打印两次任务才算完成
   }
       
}
打印“end”
释放内存
```

**SSTF策略：**

```cpp
int targetstations[TOTAL_STATION*DISTANCE]={0};
//存储当前任务下需要停靠的位置 0不停 1停
print();
getorder();
while(order=="clock")
{
    print();
    getorder();
}
while(order!="clock")
{
    creat();
    getorder();
}
findmin1();
action();
door=0;
print();

getorder();
while(order!="end")
{
    if(order=="clock")
    {
        if(门关 并且有主任务进行)
        {
            action();
            if(到站)    door=1;
        }
        else if(门关)
        {
            删除该任务
            print();
            getorder();
            if(order=="end")  break;
            while(order!="clock")
            {
                creat();
                getorder();
            }
            findmin1();
            if(没有主任务（空闲）)
            {
                action();
            }
            door=0;
            if(到站)  door=1;//特殊情况
        }
        print();
    }
    else
    {
        creat();
        findscan();
        if（当前无任务)
        {
            findmin1();
        }
    }
    getorder();
}
打印"end"
释放内存

```

**SCAN策略：**

```cpp
打印状态;
关门;
获取命令;
while(imput不为"end"){
    if(imput为"clock"){
        if(门关同时无任务){
    	    寻找下一任务;
	    if(当前有任务) 行动;
	    if(当前任务与当前位置相同) 开门;
        }
	else if（门开）{
	    结束任务;
	    寻找下一任务;
	    关门;
	}
        else if(无任务){
	    检查是否在当前位置有任务，如果有则清空;
	    寻找最短时间任务;
	    if(有任务) 行动;
	}
	打印状态;
    }
    else 录入指令；
    获取命令;
}
打印“end”
```
