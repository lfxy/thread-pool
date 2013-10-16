
#ifndef _TASK_QUEUE_
#define _TASK_QUEUE_

#include <queue>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <stdio.h>
//typedef boost::function<void(void)> TASK_FUNC; 

template<typename TASK_FUNC>
class TaskQueue:boost::noncopyable
{
public:
	TaskQueue()
	{
		m_bStop = false;
	}
	void PushTask(const TASK_FUNC & task_func)
	{
		boost::unique_lock<boost::mutex> lock(my_mutex);
		m_TaskQueue.push(task_func);
		cond.notify_one();			
	}
	TASK_FUNC TakeTask()
	{
		boost::unique_lock<boost::mutex> lock(my_mutex);
		if(m_TaskQueue.size()==0)
		{
			cond.wait(lock);
		}
		//printf("queue 1\n");
		if(m_TaskQueue.size() == 0 || m_bStop == true)
		{
			//TASK_FUNC temp;
			//return temp;
			//printf("queue 2\n");
			return NULL;
		}
		//printf("queue 3\n");
		TASK_FUNC task(m_TaskQueue.front());
		m_TaskQueue.pop();
		return task;
	}
	void stop()
	{
		m_bStop = true;
		cond.notify_all();
	}
	int GetSize()
	{
		return m_TaskQueue.size();
	}
private:
	std::queue<TASK_FUNC> m_TaskQueue;
	boost::condition_variable_any cond;
	boost::mutex my_mutex;
	bool m_bStop;
};

#endif
