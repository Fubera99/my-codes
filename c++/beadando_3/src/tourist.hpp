#ifndef TOURIST_HPP
#define TOURIST_HPP

#include <iostream>

class City;

//Parent abstract class
class Tourist
{
protected:
	int planned;
	int coming;

	Tourist(int planned) : planned(planned){};

public:
	~Tourist(){};
	int getPlanned() const { return planned; };
	int getComing() const { return coming; };

	virtual bool isJapanese() const { return false; };
	virtual bool isModern() const { return false; };
	virtual bool isOthers() const { return false; };

	virtual void checkCity(City *c){};
	virtual int damage() const { return 0; };
	double pay() const { return (coming * 0.1); };
};

class Japanese : public Tourist
{

public:
	Japanese(int planned) : Tourist(planned){};
	bool isJapanese() const override { return true; };
	void checkCity(City *c) override;
	int damage() const override { return 0; };
};

class Modern : public Tourist
{

public:
	Modern(int planned) : Tourist(planned){};
	bool isModern() const override { return true; };
	void checkCity(City *c) override;
	int damage() const override { return coming / 100; };
};

class Others : public Tourist
{

public:
	Others(int planned) : Tourist(planned){};
	bool isOthers() const override { return true; };
	void checkCity(City *c) override;
	int damage() const override { return coming / 50; };
};

#endif