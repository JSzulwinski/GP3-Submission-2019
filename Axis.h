#pragma once
#include "Object.h"

class Axis : public Object
{
public:
	Axis();

	float length;

private:
	void drawDefinition();
};

