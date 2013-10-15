
#include "ThreadPool.h"

	ThreadPool::ThreadPool(int num)
		:m_ThreadNum(num),m_IsRun(false)
	{

	}
	ThreadPool::~ThreadPool()
	{

	}
	void ThreadPool::Init()
	{
		m_IsRun = true;
		if(m_ThreadNum <= 0)
			return;
		for(int i=0; i < m_ThreadNum; ++i)
		{
			m_ThreadGroup.add_thread(new boost::thread(boost::bind(&ThreadPool::run,this)));
		}	
	}

	void ThreadPool::Stop()
	{
		m_IsRun = false;
	}

	void  ThreadPool::Post(const Task* task)
	{
		m_TaskQueue.PushTask(task);
	}

	void ThreadPool::Wait()
	{
		m_TaskQueue.stop();
		m_ThreadGroup.join_all();
	}
	
	void ThreadPool::run()
	{
		while(m_IsRun)
		{
			Task* task = const_cast<Task*>(m_TaskQueue.TakeTask()); 
			if(task != NULL)
			 {
				task->OnEvent();
		        }
			
		}
	}

