#pragma once
#include "Vector3f.h"
#include <GL/freeglut.h>

class Camera
{
public:
	Vector3f eye;
	Vector3f center;

	void update();
};

