#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>


class ThreadPool{

public:
    //构造函数
    ThreadPool(int threadCounts) :stop(false){
        // 往线程池中加线程
        for(int i = 0; i < threadCounts; i++)
        {
            threads.emplace_back([this](){ //emplace_back、push_back、拷贝构造 知识点
                while(1)
                {
                    std::unique_lock<std::mutex> lock(mutex); // unique_lock 知识点
                    condition.wait(lock,[this](){             // 信号量wait(阻塞)、this、lamda表达式 知识点
                        return !tasks.empty() || stop;
                    });

                    if(stop && tasks.empty()){
                        return ;
                    }

                    // 线程被唤醒后，取任务
                    std::function<void()> task(std::move(tasks.front())); // function、move移动语义 知识点 task包装器
                    tasks.pop();
                    lock.unlock(); // 手动解锁不用等任务结束
                    task(); // 执行任务
                }
            });
        }

    };

    // 析构函数
    ~ThreadPool(){
        {   // 这里为什么加{}
            std::unique_lock<std::mutex> lock(mutex);
            stop = true; // 线程结束
        }

        // 通知所有线程取任务，等待所有任务结束
        condition.notify_all();
        for(auto &t : threads){ // auto 自动类型推导 这里要加& 知识点
            t.join();
        }
    }

    template <class F, class... Args > // 模板类 <函数模板，可变参数列表模板> 知识点
    // 加任务（函数） 函数参数不确定所以用模板
    void enqueue(F &&f, Args&&... args){ // && 右值引用 函数模板内 右值引用就是万能引用
        std::function<void()> task = std::bind(std::forward<F>(f),std::forward<Args>(args)...);    // bind、forward（完美转发） 知识点  forward保证万能引用都能保证绑定上
        {  // lock 作用域
            std::unique_lock<std::mutex> lock(mutex);
            tasks.emplace(std::move(task));  // 队列没有back 因为添加元素的方向固定
        }
        condition.notify_one();
    };

private:

    // 线程数组和任务
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;

    //锁和信号量
    std::mutex mutex;
    std::condition_variable condition;

    // 线程池内所有线程的停止标志位
    bool stop; // 共享变量
};

int main()
{
    ThreadPool threadPool(4);
    for(int i = 0; i < 10; i++){
        threadPool.enqueue([i](){
            std::cout << "task" << i << " is running" <<  std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "task" << i << " is done" <<  std::endl;
        });
    }

    return 0;
}
