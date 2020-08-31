#include "Light.h"

Light::Light()
{
	this->id = GL_LIGHT0;
	this->enabled = false;
}

Light::Light(int id)
{
	this->id = GL_LIGHT0 + id;
	this->enabled = false;
}

void Light::update()
{
	glLightfv(id, GL_POSITION, position.v); // light position
	glLightfv(id, GL_SPOT_DIRECTION, direction.v); // light direction
	glLightfv(id, GL_AMBIENT, ambientColor.v); // background light color
	glLightfv(id, GL_DIFFUSE, diffuseColor.v); // reflected diffuse light color
	glLightfv(id, GL_SPECULAR, specularColor.v); // reflected specular light color
	glLightf(id, GL_SPOT_CUTOFF, spotCutOff); // cone of light width
	glLightf(id, GL_SPOT_EXPONENT, spotExponent); // focus of the light beam
	if (enabled)
	{
		glEnable(id); // turn on light
	} 
	else
	{
		glDisable(id); // turn off light
	}
}
