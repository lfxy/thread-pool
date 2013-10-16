#include "ThreadPool.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include "Task.h"

typedef boost::function<void(void)> my_task;

void print_task(int i)
{
	printf("I'm task %d\n",i);
}

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


int main(/*int argc, _TCHAR* argv[]*/)
{
	int thdnum = 4;
	ThreadPool<my_task> tp(thdnum);
	tp.Init();
	
	my_task t[6];
	for(int i = 0; i < 6; ++i)
	{
		t[i]=boost::bind(print_task, i + 1);
		tp.Post(t[i]);
	}
	sleep(1);
	tp.Stop();	
	tp.Wait();
	printf("stop\n");


	ThreadPool<FuncObj<Task> > tp2(thdnum);
	tp2.Init();

	Task* t2[5];
	for(int i = 0; i < 5; ++i)
	{
		ConvertToString cts;
		std::string str = cts.GetString(i + 6);
		t2[i] = new Task(str);
		FuncObj<Task> bobj(&Task::OnEvent, t2[i]);
		tp2.Post(bobj);

	}
	sleep(1);
	tp2.Stop();
	tp2.Wait();
	for(int i = 0; i < 5; ++i)
	{
		delete t2[i];
	}
	printf("stop2!\n");
	return 0;
}
