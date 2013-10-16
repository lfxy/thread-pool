#ifndef _THREAD_POOL_
#define	_THREAD_POOL_

#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

#include "TaskQueue.h"
#include "stdio.h"
//typedef boost::function<void(void)> FUNCTION_DEF;

template<typename FUNCTION_DEF>
class ThreadPool:boost::noncopyable
{
public:
/*	enum ECallType
	{
		FUNCTION_CALL = 0,
		CLASS_CALL
	};*/
	ThreadPool(int num)
		:m_ThreadNum(num),m_IsRun(false)
	{

	}
	~ThreadPool()
	{

	}
	void Init()
	{
		m_IsRun = true;
//		m_eCallType = calltype;
		if(m_ThreadNum <= 0)
			return;
		for(int i=0;i < m_ThreadNum;++i)
		{
			m_ThreadGroup.add_thread(new boost::thread(boost::bind(&ThreadPool::run,this)));
		}	
	}

	void Stop()
	{
		m_IsRun = false;
	}

	void Post(const FUNCTION_DEF& task)
	{
		m_TaskQueue.PushTask(task);
	}

	void Wait()
	{
		m_TaskQueue.stop();
		m_ThreadGroup.join_all();
	}
	

private:
	TaskQueue<FUNCTION_DEF> m_TaskQueue;
	boost::thread_group m_ThreadGroup;
	int m_ThreadNum;
	volatile bool m_IsRun;
//	ECallType m_eCallType;
//	void run();
	void run()
	{
		while(m_IsRun)
		{
			FUNCTION_DEF task=m_TaskQueue.TakeTask();
			if(task != NULL)
			{
				//printf("task != NULL\n");
				task();
			}
			/*else
			{
				printf("task == NULL\n");
			}*/
			
		}
	}

};

#endif
