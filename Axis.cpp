#include "Axis.h"

Axis::Axis()
	: Object()
{
	this->length = 30;
}

void Axis::drawDefinition()
{
	float grotX = length * 0.9f;
	float grotD = length * 0.1f;

	glBegin(GL_LINES);

	glVertex3f(-length, 0, 0);
	glVertex3f(length, 0, 0);

	glVertex3f(length, 0, 0);
	glVertex3f(grotX, grotD, 0);

	glVertex3f(length, 0, 0);
	glVertex3f(grotX, -grotD, 0);

	glVertex3f(length, 0, 0);
	glVertex3f(grotX, 0, grotD);

	glVertex3f(length, 0, 0);
	glVertex3f(grotX, 0, -grotD);

	glEnd();
}
