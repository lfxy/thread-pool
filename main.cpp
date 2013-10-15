#include "ThreadPool.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "Task.h"
//typedef boost::function<void(void)> my_task;
#include <sstream>
#include <string>


class ConvertToString
{
public:
	ConvertToString(){}
	~ConvertToString(){}
	template<typename T>
	std::string& GetString(const T& type)
	{
		ss.str("");
		ss.clear();
		ss<<type;
		strOutPut.assign(ss.str());
		return strOutPut;
	}
private:
	std::ostringstream ss;
	std::string strOutPut;
};

void print_task(int i)
{
	printf("I'm task %d\n",i);
}

int main(/*int argc, _TCHAR* argv[]*/)
{
	int thdnum = 4;
	ThreadPool tp(thdnum);
	tp.Init();
	
	//my_task* t[6];
	Task* t[6];
	for (int i= 0; i < 6; ++i)
	{
		ConvertToString cts;
		std::string snum = cts.GetString(i);
		t[i] = new Task(snum);
		//t[i]=boost::bind(print_task,i+1);
		tp.Post(t[i]);
	}
	sleep(1);
	tp.Stop();	
	printf("stop\n");
	tp.Wait();
	printf("wait\n");
	for(int i = 0; i < 6; ++i)
	{
		delete t[i];
	}
	printf("stop1\n");

	return 0;
}
