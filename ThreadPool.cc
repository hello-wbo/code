#include <iostream>
#include "ThreadPool.h"

using namespace std;

ThreadPool::ThreadPool(size_t num):stop(false)
{
    for(int i=0;i<num;++i)
        threads.emplace_back(&ThreadPool::entry,this);
}

void ThreadPool::entry()
{
    while(1)
    {
        unique_lock<mutex> lock(task_mutex);
        // ���������Ϊ�����̳߳�����״̬ʱ�Ż������������ѿ��������������������������̳߳�׼��ֹͣ
        cond.wait(lock,[this]{return this->stop||!this->tasks.empty();});
        // ������̳߳�ֹͣ�����˳����߳�
        if(stop)
            return;

        // ����ʹ����������ȡ�ǰ��һ���������ִ�У������������
        Task cur_task = std::move(tasks.front());
        tasks.pop();
        lock.unlock();// taskȡ����Ϳ��Խ���
        cur_task();
    }
}

ThreadPool::~ThreadPool()
{
    cout<<"delete pool!"<<endl;
    if(!stop)
        shutdown();
}

void ThreadPool::shutdown()
{
    // �޸�stopΪtrue��֪ͨ�����̳߳��е��߳�
    {
        unique_lock<mutex> lock(task_mutex);
        stop = true;
    }
    cond.notify_all();
    // ͬʱ�ȴ����߳�ִ�����
    for(auto &th: threads)
        th.join();
}