#ifndef FOOD_H
#define FOOD_H
#include "point.h"

class food
{
public:
	food();
	food(unsigned value);
	food(point location, unsigned value);
	~food();

	unsigned getValue();
	point getLocation();
private:
	point location;
	unsigned value;
};

#endif
