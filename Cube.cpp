#include "Cube.h"

Cube::Cube()
	: Object()
{
	this->size = Vector3f(0.5, 0.5, 0.5);
}

void Cube::drawDefinition()
{
	glColor3fv(color.v);
	drawCube();
}
