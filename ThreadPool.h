#ifndef _THREAD_POOL_
#define	_THREAD_POOL_

#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

#include "TaskQueue.h"
#include "stdio.h"
#include "Task.h"
//typedef boost::function<void(void)> FUNCTION_DEF;

class ThreadPool:boost::noncopyable
{
public:
	ThreadPool(int num);
	~ThreadPool();
	void Init();
	void Stop();
	void  Post(const Task* ptask);
	void Wait();
	
private:
	TaskQueue m_TaskQueue;
	boost::thread_group m_ThreadGroup;
	int m_ThreadNum;
	volatile bool m_IsRun;
	void run();
};

#endif
