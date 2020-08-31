#pragma once
#include "Vector3f.h"
#include "Vector4f.h"
#include <GL/freeglut.h>

class Object
{
public:
	Object();

	Vector3f position;
	Vector3f scale;
	Vector3f angle;
	Vector3f color;
	GLuint texture;

	Vector3f size;
	Vector3f collisionBoxColor;

	bool possibleCollision;
	bool showCollisionBox;
	bool visible;
	
	void draw();

protected:
	virtual void drawDefinition() = 0;
	
	void drawCube();
	void drawCollisionBox();
};

