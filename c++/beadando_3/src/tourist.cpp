#include "tourist.hpp"
#include "city.hpp"

//Japanese----------------------------------------------------

void Japanese::checkCity(City *c)
{
	int status = c->getStatus();
	if (status <= 33)
		coming = 0;
	else if (status >= 68)
		coming = (int)(planned * 1.2);
	else
		coming = planned;
}

//Modern------------------------------------------------------

void Modern::checkCity(City *c)
{
	int status = c->getStatus();
	if (status >= 68)
		coming = (int)(planned * 1.3);
	else if (status >= 34)
		coming = (int)(planned * 1.1);
	else
		coming = planned;
}

//Others------------------------------------------------------

void Others::checkCity(City *c)
{
	int status = c->getStatus();
	if (status >= 34 && status <= 67)
		coming = (int)(planned * 1.1);
	else
		coming = planned;
}
