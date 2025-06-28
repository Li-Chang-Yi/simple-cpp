#include <iostream>
#include <csignal> //program信号头文件
#include <unistd.h> //unistd = UNIX standard 包含 POSIX(Portable可移植的 Operating System Interface, X =UNIX ) 操作系统接口标准头文件 有fork() exec() getpid() chdir() sleep()
#include <pthread.h> // 线程相关头文件

#include <thread>
#include <chrono>
using namespace std;
// 两部分代码的开关
//#define signal_code
#define thread_code

#ifdef signal_code
void signalHandler( int signum )
{
    cout << "Interrupt signal (" << signum << ") received.\n";
    // 终止程序
   exit(signum);

}
int main ()
{
    signal(SIGINT, signalHandler); // signal()函数 ：signal(registered signal, signal handler) 作用：注册信号 SIGINT 和信号处理程序
//    while(1){
//        cout << "Going to sleep...." << endl;  // 按 Ctrl+C 来中断程序，您会看到程序捕获打断信号INT
//        sleep(1);
//    }

    // raise()函数 ：int raise (signal sig);
    int i = 0;
    while(++i){
        cout << "Going to sleep...." << endl;
        if( i == 3 ){
            raise( SIGINT); // 函数 raise() 生成信号
        }
        sleep(1); // 1s
    }
    return 0;
}
#endif
//SIG-ABRT	（Abort）程序的异常终止，如调用abort。
//SIG-FPE	（Floating-Point Exception）错误的算术运算，比如除以零或导致溢出的操作。
//SIG-ILL	（Illegal Instruction）检测非法指令。
//SIG-INT	程序终止(interrupt)信号。
//SIG-SEGV	（Segmentation Violation（违反））非法访问内存，程序尝试访问它没有权限访问的内存区域（“段错误”（segmentation fault））。
//SIG-TERM	（Terminate）发送到程序的终止请求。
//SIG-HUP   程序挂起

// 多线程知识
#ifdef thread_code
#define NUM_THREADS 5

// 线程运行函数（传指针）,返回值和参数都是无类型指针 void*
void* PrintVar(void* threadid)
{
   // 对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
   int tid = *( (int*) threadid );
   cout << "In thread callback function and thread ID:" << tid << endl;
   pthread_exit(NULL);
}
// 线程运行函数（传结构体指针）
// 定义结构体，用于传递数据给线程
struct ThreadData {
    int number;
    std::string message;
};
void* ThreadFunction(void* arg) {
    // 转换arg为原来的结构体指针类型
    ThreadData* data = (ThreadData*) arg;
//    ThreadData* data = static_cast<ThreadData*>(arg); // static_cast 是类型转换运算符之一，用于在相关类型之间进行显式转换。这种转换在编译时进行检查，而不是在运行时，因此它叫做“静态”转换
    // 输出接收到的数据
    std::cout << "Number: " << data->number << ", Message: " << data->message << std::endl;
    // 清理传入的指针
    delete data;
    // 退出线程
    pthread_exit(NULL);
}
// 连接和分离线程 join和detach
// pthread_join函数会阻塞调用它的线程（通常是主线程），直到指定的线程结束。它的资源不会自动释放，需要通过pthread_join来回收
// pthread_detach函数会将指定的线程标记为detached状态，这样当这个线程结束时，它的资源会自动被操作系统回收。一旦线程被detach，就不能再join了
// 线程函数
void* thread_func(void* arg)
{
    string threadname = * (string*) arg;
    // printf函数中，您应该使用c_str()方法从std::string对象中获取C风格的字符串：
    printf("%s started. Sleeping for 2 seconds...\n", threadname.c_str());
    sleep(2);  // 模拟线程工作，休眠2秒
    printf("%s ending...\n", threadname.c_str());
    return NULL;
}


int main ()
{
    pthread_t threads[NUM_THREADS]; // 定义线程的 id 变量，多个变量使用数组
    int indexes[NUM_THREADS];// 用数组来保存i的值
    int ret,i,rc;
//    for( i=0; i < NUM_THREADS; i++ )
//    {
//       cout << "main(): create thread " << i << endl;
//       indexes[i] = i; //在一个数组中存放i的值，方便用地址取出来
//       //参数依次是：创建的线程id，线程参数，回调函数，传入参数
//       // 传入的时候必须强制转换为void* 类型，即无类型指针
//       ret = pthread_create(&threads[i], NULL, PrintVar, (void *) &indexes[i] );
//       if (ret) //返回1，则未创建线程成功
//       {
//          cout << "Error:unable create thread," << ret << endl;
//          exit(-1);
//       }
//    }

    pthread_t thread;
    // 分配新的ThreadData
    ThreadData* data = new ThreadData;
    // 填充结构体数据
    data->number = 42;
    data->message = "Hello from thread";
    // 创建线程，传递结构体指针作为参数
    if (pthread_create(&thread, NULL, ThreadFunction, data)) {
        std::cerr << "Error creating thread\n";
        delete data; // 如果线程创建失败，需要清理内存
        return 1;
    }

    if( pthread_join(thread, NULL) != 0 )     // 使用join等待线程结束
    {
        perror("Failed to join the thread");
        return 2;

    };
    printf("Joined the thread successfully.\n");

    // join 和 detach
    pthread_t thread1;
    string threadname1 = "thread1";
    // 创建线程1
    if (pthread_create(&thread1, NULL, thread_func, &threadname1) != 0) {
        perror("Failed to create the thread1");
        return 1;
    }
    // 使用join等待线程结束 : pthread_join (threadid, status)
    if (pthread_join(thread1, NULL) != 0)
    {
        perror("Failed to join the thread1");
        return 2;
    }
    printf("Joined the thread1 successfully.\n");

    pthread_t thread2;
    // 创建线程2
    string threadname2 = "thread2";
    if (pthread_create(&thread2, NULL, thread_func, &threadname2) != 0)
    {
        perror("Failed to create thread2");
        return 1;
    }
    if (pthread_detach(thread2) != 0)  // 使用detach使线程在结束时自动清理资源 : pthread_detach (threadid)
    {
        perror("Failed to detach the thread2");
        return 2;
    }
    printf("Detached thread2 successfully.\n");

    sleep(3);    // 给detached线程足够的时间来完成

    printf("Main thread ending...\n");
    return 0;

}
#endif
