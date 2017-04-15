# LIMS_SERVER

> 实验室管理系统的服务器，负责与客户端进行交互，解析并处理客户端的请求，同时完成与数据库的对接。

## 服务器主要分为五个模块
> 1. CommModule：负责通信部分，将收到的数据递交上层处理。
>2. RequestBuffPool:收到通信模块递交的数据后，根据客户端的IP地址存储在队列中，维护一个ClientRequest队列。
>3. RequestParseModule:客户端请求的解析模块。从缓冲池中取出客户端的请求，解析后根据请求类型调用DatabaseModule模块对数据库进行操作。
处理完成后，将数据返回给ClientRequest实例
>4. DataseModule：数据库模块。实现了数据库操作的一些接口。单例模式，只提供一个实体。
>5. LogModule：日志模块，单例模式，实现不同模块打印日志到主窗口

## 2017-04-15
1. 需要增加通信鉴权模块 

## 2017-03-12
### 疑问
1. 多线程收发问题


## 2017-03-10 
### TODO
1. 将请求解析的处理结果返回给客户端


## 2017-3-9 
### 多线程分析：
1. 主线程：包括MainWindowhe LogModule，并管理子线程RequestParseModule，
2. 子线程RequestParseModule：与DatabaseModule位于同一线程，同时管理子线程RequestBuffPool
3. 子线程RequestBuffPool：与CommModule、ClientRequest位于同一线程。

在MainWindow的构造函数中直接实例化RequestParseModule对象，此时只有在RequesParseModule线程的run()函数部分才属于子线程，其他部分仍由主线程管理。所以要在run()函数中将单例的DatabaseModule对象移到子线程中（databaseModule.moveToThread(this)。而RequestBuffPool线程则可以直接在构造函数中新建。
同样的，需要在RequestBuffPool的run()中将CommModule移到本线程中。

### TODO
1. **DatabaseModule和CommModule模块不使用单例模式实现**
2. 请求解析模块解析完成后直接由ClientRequest将处理结果返回

### 疑问
1. 子线程中exec()的使用
    * 当在run中使用了qt的信号——槽时，即表明需要进入该线程的事件循环，调用thread.exec()。
    * 当在run中使用自己的循环来处理时，不需要进入事件循环。



## 2017-3-7
1. 目前使用的多线程为使用独立线程的模块集成QThread，但是这种使用方式是只有run()函数中的语句才会在子线程中执行，其他地方的语句以及创建的对象都属于主线程。可以在每个需要在子线程中执行的模块在实现时先不集成QThread，只集成QObject。在主线程中创建该模块的对象，并且创建一个QThread对象，然后使用moveToThread()方法将模块转移到该子线程中。

2. RequestParseModule和RequestBuffPool为两个运行在不同子线程的模块，两个模块的关系类似于生产者-消费者，RequestBuffPool生产数据——即从CommModule模块中获取客户端的请求，RequestParseModule模块从中取出请求——即消费，考虑使用信号量来进行线程之间的同步。


## 2017-3-3
### 存在的问题
1. 是否用多线程实现（每个模块一个线程？）
2. 如何导入初始数据