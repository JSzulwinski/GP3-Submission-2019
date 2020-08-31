#pragma once
#include "Vector3f.h"
#include "Vector4f.h"
#include <GL/freeglut.h>

class Light
{
public:
	Light();
	Light(int id);

	void update();

	Vector4f position;
	Vector3f direction;
	Vector4f ambientColor;
	Vector4f specularColor;
	Vector4f diffuseColor;
	float spotCutOff = 95; // cone of light width
	float spotExponent = 60; // focus of the light beam
	bool enabled;

private:
	int id;

};

