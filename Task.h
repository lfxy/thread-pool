#include <string>
#include <iostream>
#include <stdio.h>

template<typename obj>
class FuncObj
{
public:
	FuncObj(void (obj::*func)(), obj* o = NULL)
	: m_pFunc(func),
	  m_pObj(o)
	{
	}
	void operator()()
	{
		(m_pObj->*m_pFunc)();
	}
	bool operator==(FuncObj<obj> b)
	{
		if(this == NULL)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	bool operator!=(FuncObj<obj> b)
	{
		/*if(b == NULL)
		{
			printf("task 1\n");
			return false;
		}
		else */if(this->m_pObj != b.m_pObj || this->m_pFunc != b.m_pFunc)
		{
			//printf("task 2\n");
			return true;
		}
		else
		{
			//printf("task 3\n");
			return false;
		}		
	}

	FuncObj<obj>& operator=(FuncObj& b)
	{
		this->m_pObj = b.m_pObj;
		this->m_pFunc = b.m_pFunc;
		return (*this);
	}
private:
	void (obj::*m_pFunc)();
	obj* m_pObj;
};


class Task
{
public:
	Task(){}
	Task(std::string& str)
	: m_strPrint(str)
	{

	}
	~Task(){}
	void InitTask(std::string sOut)
	{
		m_strPrint = sOut;
	}
	void OnEvent()
	{
		std::cout<<"I am task:"<<m_strPrint<<std::endl;
	}	
	
private:
	std::string m_strPrint;
};
