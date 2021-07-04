#include "city.hpp"

City *City::instance = nullptr;
City *City::getInstance()
{
	if (instance == nullptr)
	{
		instance = new City();
		instance->status = 0;
		instance->income = 0;
	}
	return instance;
}

void City::destroy()
{
	if (nullptr != instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void City::setStatus(int s)
{
	status = s;
	if (status < 1)
		status = 1;
	else if (status > 100)
		status = 100;
}

void City::hosts(Tourist *t)
{
	status -= t->damage();
	if (status < 1)
		status = 1;
	income += t->pay();
}

void City::repair()
{
	if (income > 1000)
	{
		income = income - 1000;
		status += (int)(income / 20);
	}
	income = 0;
	if (status > 100)
		status = 100;
}

std::string City::getStatusWord() const
{
	if (status < 34)
		return "poor";
	else if (status < 68)
		return "average";
	else
		return "good";
}