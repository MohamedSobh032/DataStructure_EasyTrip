#include "TimeHM.h"
#include <iostream>

TimeHM::TimeHM()
{
	this->hours = 0;
	this->minutes = 0;
	this->seconds = 0;
}
TimeHM::TimeHM(int h, int m, int s)
{
	this->hours = h;
	this->minutes = m;
	this->seconds = s;
}

void TimeHM::setHours(int h)
{
	this->hours = h;
}
void TimeHM::setMinutes(int m)
{
	this->minutes = m;
}
void TimeHM::setSeconds(int s)
{
	this->seconds = s;
}

int TimeHM::getHours() const
{
	return this->hours;
}
int TimeHM::getMinutes() const
{
	return this->minutes;
}
int TimeHM::getSeconds() const
{
	return this->seconds;
}


void TimeHM::display() {
	std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
}

TimeHM::~TimeHM()
{

}