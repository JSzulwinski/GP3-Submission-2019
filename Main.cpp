#include <GL/freeglut.h>
#include "Vector3f.h"
#include "Vector4f.h"
#include "Axis.h"
#include "Cube.h"
#include "Scene.h"

Axis* axisX;
Axis* axisY;
Axis* axisZ;
Cube* ground;
Cube* cube1;
Cube* cube2;
Cube* cube3;
bool showAxis = true;

// Keyboard controls
void keyboardKeys(Scene *scene, unsigned char key, int mouseX, int mouseY)
{
	float step = 3.0; 
	if (key == ' ')
	{
		showAxis = !showAxis;
		axisX->visible = showAxis;
		axisY->visible = showAxis;
		axisZ->visible = showAxis;
	}
	else if (key == 'q')
	{
		cube1->angle.y += step;
	}
	else if (key == 'w')
	{
		cube1->angle.y -= step;
	}
	else if (key == 'f')
	{
		scene->setFullScreen(!scene->isFullScreen());
	}
	else if (key == VK_ESCAPE)
	{
		glutExit();
	}

}

// Special keys
void specialKeys(Scene* scene, int key, int mouseX, int mouseY)
{
	float step = 1.0;
	if (key == GLUT_KEY_RIGHT)
		cube1->position.x += step;
	else if (key == GLUT_KEY_LEFT)
		cube1->position.x -= step;
	else if (key == GLUT_KEY_UP)
		cube1->position.y += step;
	else if (key == GLUT_KEY_DOWN)
		cube1->position.y -= step;
	else if (key == GLUT_KEY_PAGE_UP)
		cube1->position.z += step;
	else if (key == GLUT_KEY_PAGE_DOWN)
		cube1->position.z -= step;
}

// Mouse buttons
void mouseButton(Scene* scene, int button, int state, int mouseX, int mouseY)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

// Moving mouse with button pressed
void mouseMoveActive(Scene* scene, int mouseX, int mouseY)
{
	
}

// Moving mouse without button pressed
void mouseMovePassive(Scene* scene, int mouseX, int mouseY)
{
	scene->camera.eye.x = mouseX - scene->getWidth() / 2.f;
	scene->camera.eye.y = scene->getHeight() / 2.f - mouseY;
}

int main(int argc, char* argv[])
{
	Scene scene("Framework OpenGL", 0, 0, 500, 500);

	scene.setKeyboardFunction(keyboardKeys);
	scene.setSpecialFunction(specialKeys);
	scene.setMouseButtonFunction(mouseButton);
	scene.setMouseMoveActiveFunction(mouseMoveActive);
	scene.setMouseMovePassiveFunction(mouseMovePassive);
	scene.setFrameRate(30); // 30 fps
	scene.setFullScreen(true);

	scene.camera.eye = Vector3f(0, 0, 25); // camera
	scene.camera.center = Vector3f(0, 0, 0); // point of observation
	scene.backgroundColor = Vector3f(0.0f, 0.2f, 0.5f); // background color
	scene.lightAmbient = Vector4f(0.3f, 0.3f, 0.3f); // ambient light

	// Light 0
	scene.light[0].position = Vector4f(2, 10, 10);
	scene.light[0].direction = Vector3f(-2, -10, -10);
	scene.light[0].ambientColor = Vector4f(0, 0, 0);
	scene.light[0].specularColor = Vector4f(1, 1, 1);
	scene.light[0].diffuseColor = Vector4f(1, 1, 1);
	scene.light[0].spotCutOff = 95;
	scene.light[0].spotExponent = 60;
	scene.light[0].enabled = true;

	// Light 1
	scene.light[1].position = Vector4f(-10, -2, 10);
	scene.light[1].direction = Vector3f(10, 2, -10);
	scene.light[1].ambientColor = Vector4f(0, 0, 0);
	scene.light[1].specularColor = Vector4f(1, 1, 0.5);
	scene.light[1].diffuseColor = Vector4f(1, 1, 0.5);
	scene.light[1].spotCutOff = 95;
	scene.light[1].spotExponent = 60;
	scene.light[1].enabled = true;

	GLuint textureGrass = scene.addTexture("textures\\grass.bmp");
	GLuint textureRed = scene.addTexture("textures\\red.bmp");
	GLuint textureWoodedBox = scene.addTexture("textures\\woodedBox.bmp");
	GLuint textureGround = scene.addTexture("textures\\ground.bmp");

	axisX = new Axis();
	axisX->color = Vector3f(1, 0, 0);
	scene.addObject(axisX);

	axisY = new Axis();
	axisY->color = Vector3f(0, 1, 0);
	axisY->angle.z = 90;
	scene.addObject(axisY);

	axisZ = new Axis();
	axisZ->color = Vector3f(0, 0, 1);
	axisZ->angle.y = -90;
	scene.addObject(axisZ);

	ground = new Cube();
	ground->scale = Vector3f(40, 1, 40);
	ground->texture = textureGround;
	ground->position.y = -2.5;
	ground->possibleCollision = true;
	scene.addObject(ground);

	cube1 = new Cube();
	cube1->position.x = -5;
	cube1->scale = Vector3f(4, 4, 4);
	cube1->texture = textureGrass;
	cube1->possibleCollision = true;
	scene.addObject(cube1);

	cube2 = new Cube();
	cube2->position.x = 5;
	cube2->scale = Vector3f(4, 4, 4);
	cube2->texture = textureRed;
	cube2->possibleCollision = true;
	scene.addObject(cube2);

	cube3 = new Cube();
	cube3->position.z = 10;
	cube3->scale = Vector3f(4, 4, 4);
	cube3->texture = textureWoodedBox;
	cube3->possibleCollision = true;
	scene.addObject(cube3);

	scene.start();
	
	return EXIT_SUCCESS;
}




