#include"Time.h"
#include<print>

void Time::printTime()const
{
	std::println("{:02}:{:02}", hour, min);
}