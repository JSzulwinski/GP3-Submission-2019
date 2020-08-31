#include "Object.h"

class Scene;

Object::Object()
	: possibleCollision(false), showCollisionBox(false), texture(NULL), visible(true),
	collisionBoxColor(Vector3f::one()), scale(Vector3f::one()), size(Vector3f::one()), color(Vector3f::one())
{
}

void Object::draw()
{
	if (!visible) return;

	glPushMatrix();
	
	glTranslatef(position.x, position.y, position.z);
	glRotatef(angle.x, 1, 0, 0);
	glRotatef(angle.y, 0, 1, 0);
	glRotatef(angle.z, 0, 0, 1);
	glScalef(scale.x, scale.y, scale.z);

	if (showCollisionBox) drawCollisionBox();

	if (texture)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, NULL);
	}

	glColor3fv(color.v);
	this->drawDefinition();
	
	glPopMatrix();
}

void Object::drawCube()
{
	glBegin(GL_QUADS);

	glNormal3f(1.f, 0.f, 0.f);
	glTexCoord2f(1.f, 0.f); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.f, 1.f); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.f, 1.f); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.f, 0.f); glVertex3f(0.5, -0.5, 0.5);
								 
	glNormal3f(-1.f, 0.f, 0.f);
	glTexCoord2f(0.f, 0.f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.f, 1.f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.f, 1.f); glVertex3f(-0.5f, 0.5f, -0.5f);
								 
	glNormal3f(0.f, 1.f, 0.f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.f, 1.f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.f, 1.f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.f, 0.f); glVertex3f(0.5f, 0.5f, -0.5f);
								 
	glNormal3f(0.f, -1.f, 0.f);
	glTexCoord2f(1.f, 0.f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.f, 1.f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.f, 1.f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.f, 0.f); glVertex3f(-0.5f, -0.5f, -0.5f);
								 
	glNormal3f(0.f, 0.f, 1.f);
	glTexCoord2f(0.f, 0.f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.f, 0.f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.f, 1.f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.f, 1.f); glVertex3f(-0.5f, 0.5f, 0.5f);
								 
	glNormal3f(0.f, 0.f, -1.f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.f, 1.f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.f, 1.f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.f, 0.f); glVertex3f(0.5f, -0.5f, -0.5f);

	glEnd();
}

void Object::drawCollisionBox()
{
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glColor3fv(collisionBoxColor.v);

	glPushMatrix();
	glScalef(1.1f, 1.1f, 1.1f);

	glBegin(GL_LINE_LOOP);
	glVertex3f(size.x, size.y, size.z);
	glVertex3f(-size.x, size.y, size.z);
	glVertex3f(-size.x, size.y, -size.z);
	glVertex3f(size.x, size.y, -size.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(size.x, -size.y, size.z);
	glVertex3f(-size.x, -size.y, size.z);
	glVertex3f(-size.x, -size.y, -size.z);
	glVertex3f(size.x, -size.y, -size.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(size.x, size.y, size.z);
	glVertex3f(size.x, -size.y, size.z);

	glVertex3f(-size.x, size.y, size.z);
	glVertex3f(-size.x, -size.y, size.z);

	glVertex3f(size.x, size.y, -size.z);
	glVertex3f(size.x, -size.y, -size.z);

	glVertex3f(-size.x, size.y, -size.z);
	glVertex3f(-size.x, -size.y, -size.z);
	glEnd();

	glPopMatrix();
}
