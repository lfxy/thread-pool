#ifndef _TASK_DEF_
#define _TASK_DEF_
   
#include <string>
#include <stdio.h>

class Task
{
public:
	Task(){}
	Task(std::string& str)
	:m_strPrint(str)
	{
	}
	~Task(){}
	void InitTask(std::string& sOut)
	{
		m_strPrint = sOut;
	}
	void OnEvent()
	{
		printf("task: %s\n", m_strPrint.c_str());
	}	
	
private:
	std::string m_strPrint;
};
#endif
