
#include "TaskQueue.h"
#include <stdio.h>

	TaskQueue::TaskQueue()
	{
		m_bStop = false;
	}
	void TaskQueue::PushTask(const Task* task_func)
	{
		boost::unique_lock<boost::mutex> lock(my_mutex);
		m_TaskQueue.push(task_func);
		cond.notify_one();			
	}
	const Task* TaskQueue::TakeTask()
	{
		boost::unique_lock<boost::mutex> lock(my_mutex);
		if(m_TaskQueue.size()==0)
		{
			cond.wait(lock);
		}
		if(m_TaskQueue.size() == 0 || m_bStop == true)
		{
			return NULL;
		}
		const Task* task(m_TaskQueue.front());
		m_TaskQueue.pop();
		return task;
	}
	void TaskQueue::stop()
	{
		m_bStop = true;
		cond.notify_all();
	}
	int TaskQueue::GetSize()
	{
		return m_TaskQueue.size();
	}
