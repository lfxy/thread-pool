
#ifndef _TASK_QUEUE_
#define _TASK_QUEUE_

#include <queue>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include "Task.h"

//typedef boost::function<void(void)> TASK_FUNC; 

class TaskQueue:boost::noncopyable
{
public:
	TaskQueue();
	void PushTask(const Task* task_func);
	const Task* TakeTask();
	void stop();
	int GetSize();
private:
	std::queue<const Task*> m_TaskQueue;
	boost::condition_variable_any cond;
	boost::mutex my_mutex;
	bool m_bStop;
};

#endif
