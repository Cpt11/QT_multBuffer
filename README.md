# QT_multBuffer

**题目**1**：多道程序缓冲区协同操作**

设自行车生产线上有3只箱子（BOX），箱中有N个位置（N>=2），BOX1每个位置可存放下一个车架，BOX2每个位置可存放一个车轮，BOX3每个位置可存放下一台组装好的车。设有3个（类）工人，工人1不断地向箱1中放车架，工人2不断地向箱2中放车轮，工人3不断地从箱中1取出一个车架和箱2中取2个轮子，组装成一台自行车，并把它放到BOX3中。任何一个时刻对某一箱子只能有1个工人对箱子操作。有很多个搬运工（Carrier）不停地将BOX3取出运走。其活动可分别可以抽象为图1。

采用多进程或多线程方式，运用同步和互斥机制，设计一个多道程序完成上述任务和操作。

提示：需要设计 Worker1、Worker2、Worker3、Carrier类线程                        

![image-20240102104643716](https://gitee.com/cpt11/csdn-image/raw/master/image-20240102104643716.png) 

**基本功能要求**

（1） 提供良好图形界面，显示整个系统操作过程，~~可以暂停和继续系统的执行；~~

~~(2) 可以设定各BOX容量；~~

(3) 可以设定PUT、GET、Move操作的速度；

(4) 实时显示每个BOX中当前物品的数量，空闲空间的数量；

(5) 实时显示线程、进程所处于等待（阻塞）状态的个数；

~~（6）程序运行结束，显示汇总数据：总的运行时间；处理个物品的个数；平均每个BOX中的物品个数。~~

~~（7） 能够将每次的实验输入和实验结果存储起来，随时可查询。~~ 

   **可以根据题目的基本要求进行丰富的创意和想象，并在设计说明书中说明创意和创新的新功能，描述项目实现的特点和特色**。

> qt6 实现ui界面  部分功能没有实现 
>
> 原理就是一个生产者消费者模式 + QT多线程 
>
> MultBuffer.rar 为打包程序 

程序截图 ： 

![image-20240102104829986](https://gitee.com/cpt11/csdn-image/raw/master/image-20240102104829986.png)
