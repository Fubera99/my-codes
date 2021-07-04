#ifndef CITY_HPP
#define CITY_HPP

#include "tourist.hpp"
#include <string>

class City
{
private:
	int numberOfYears;
	int status;
	double income; //n million HUF
	static City *instance;

	City(){};

public:
	~City(){};

	void hosts(Tourist *t);
	void repair();

	int getStatus() const { return status; };
	std::string getStatusWord() const;
	void setStatus(int status);

	double getIncome() const { return income; };

	int getNumberOfYears() const { return numberOfYears; };
	void setNumberOfYears(int numberOfYears) { this->numberOfYears = numberOfYears; };

	static void destroy();

	static City *getInstance();
};

#endif