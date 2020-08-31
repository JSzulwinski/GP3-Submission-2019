#include <windows.h> /*windows header*/

#include <gl/gl.h>/*opengl32 header*/
#include <gl/glu.h>/*glu32 header*/
#include <gl/freeglut.h> /*freeglut header*/

#define _USE_MATH_DEFINES
#include <cmath>

#include "Object.h"
#include "Scene.h"

Scene* Scene::instance = NULL;

Scene::Scene(const char* windowCaption, int windowPosX, int windowPosY, int windowWidth, int windowHeight)
	: fullScreen(false), renderInterval(1000/40), keyboardFunction(NULL), specialFunction(NULL), mouseButtonFunction(NULL), mouseMoveActiveFunction(NULL), mouseMovePassiveFunction(NULL)
{
	this->instance = this;
	this->quadricParts = 40;

	this->windowPosX = windowPosX;
	this->windowPosY = windowPosY;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	int _argc = 0;
	glutInit(&_argc, NULL);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_BORDERLESS*/);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutInitWindowSize(windowWidth, windowHeight);
	windowHandle = glutCreateWindow(windowCaption);
	glutDisplayFunc(glutRenderFunction);
	glutReshapeFunc(glutReshapeFunction);

	glEnable(GL_DEPTH_TEST); // turn on depth buffer
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// quadric drawing configuration
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);
	gluQuadricTexture(quadric, GL_FALSE);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	for (int i = 0; i < 8; i++)
	{
		light[i] = Light(i);
	}

	// Global light
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); // turn on lighting
}

Scene::~Scene()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}

	for (size_t i = 0; i < textures.size(); i++)
	{
		GLuint texture = textures[i];
		glDeleteTextures(1, &texture);
	}

	gluDeleteQuadric(quadric);
	glutDestroyWindow(windowHandle);
}

void Scene::setKeyboardFunction(void (*keyboardFunction)(Scene* scene, unsigned char key, int mouseX, int mouseY))
{
	this->keyboardFunction = keyboardFunction;
	glutKeyboardFunc(glutKeyboardFunction);
}

void Scene::setSpecialFunction(void (*specialFunction)(Scene* scene, int key, int mouseX, int mouseY))
{
	this->specialFunction = specialFunction;
	glutSpecialFunc(glutSpecialFunction);
}

void Scene::setMouseButtonFunction(void (*mouseButtonFunction)(Scene* scene, int button, int state, int mouseX, int mouseY))
{
	this->mouseButtonFunction = mouseButtonFunction;
	glutMouseFunc(glutMouseButtonFunction);
}

void Scene::setMouseMoveActiveFunction(void (*mouseMoveActiveFunction)(Scene* scene, int mouseX, int mouseY))
{
	this->mouseMoveActiveFunction = mouseMoveActiveFunction;
	glutMotionFunc(glutMouseMoveActiveFunction);
}

void Scene::setMouseMovePassiveFunction(void (*mouseMovePassiveFunction)(Scene* scene, int mouseX, int mouseY))
{
	this->mouseMovePassiveFunction = mouseMovePassiveFunction;
	glutPassiveMotionFunc(glutMouseMovePassiveFunction);
}

void Scene::setFrameRate(int fps)
{
	this->renderInterval = 1000 / fps;
	glutTimerFunc(this->renderInterval, glutTimerFunction, (int)this);
}

void Scene::setFullScreen(bool fullScreen)
{
	this->fullScreen = fullScreen;
	if (fullScreen) 
	{
		glutFullScreen();
	}
	else
	{
		glutReshapeWindow(windowWidth, windowHeight);
		glutPositionWindow(windowPosX, windowPosY);
	}
}

int Scene::getWidth()
{
	return windowWidth;
}

int Scene::getHeight()
{
	return windowHeight;
}

bool Scene::isFullScreen()
{
	return fullScreen;
}

void Scene::addObject(Object* object)
{
	objects.push_back(object);
}

void Scene::start()
{
	glutMainLoop();
}

void Scene::glutKeyboardFunction(unsigned char key, int mouseX, int mouseY)
{
	if (instance->keyboardFunction) instance->keyboardFunction(instance, key, mouseX, mouseY);
}

void Scene::glutSpecialFunction(int key, int mouseX, int mouseY)
{
	if (instance->specialFunction) instance->specialFunction(instance, key, mouseX, mouseY);
}

void Scene::glutMouseButtonFunction(int button, int state, int mouseX, int mouseY)
{
	if (instance->mouseButtonFunction) instance->mouseButtonFunction(instance, button, state, mouseX, mouseY);
}

void Scene::glutMouseMoveActiveFunction(int mouseX, int mouseY)
{
	if (instance->mouseMoveActiveFunction) instance->mouseMoveActiveFunction(instance, mouseX, mouseY);
}

void Scene::glutMouseMovePassiveFunction(int mouseX, int mouseY)
{
	if (instance->mouseMovePassiveFunction) instance->mouseMovePassiveFunction(instance, mouseX, mouseY);
}

void Scene::render()
{
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //window and depth buffer clearing

	//projection matrix needed for perspective
	glMatrixMode(GL_PROJECTION);
	//set actual matrix to I (reset matrix to its original state)
	glLoadIdentity();

	//set perspective
	gluPerspective(60, (float)windowWidth / (float)windowHeight, 1.0, 1000.0);

	//camera
	camera.update();

	//transformation model matrices affect model matrix
	glMatrixMode(GL_MODELVIEW);
	//set actual matrix to I
	glLoadIdentity();

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient.v);
	for (int i = 0; i < 8; i++)
	{
		if (light[i].enabled) light[i].update();
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->showCollisionBox = false;
	}

	for (size_t i = 0; i < objects.size() - 1; i++)
	{
		Object* a = objects[i];
		for (size_t j = i + 1; j < objects.size(); j++)
		{
			if (i != j && i )
			{
				Object* b = objects[j];
				if (a->possibleCollision && b->possibleCollision)
				{
					if (checkCollision(a, b))
					{
						a->showCollisionBox = true;
						b->showCollisionBox = true;
					}
				}
			}
		}
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->draw();
	}

	glFlush();
	glutSwapBuffers();
}

void Scene::glutRenderFunction()
{
	instance->render();
}

void Scene::glutReshapeFunction(int width, int height)
{
	instance->resize(width, height);
}

void Scene::glutTimerFunction(int sceneCallback)
{
	Scene* scene = (Scene*)sceneCallback;
	glutPostRedisplay();
	glutTimerFunc(scene->renderInterval, glutTimerFunction, sceneCallback);
}

void Scene::resize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;

	if (height == 0) height = 1;
	if (width == 0) width = 1;

	//viewport settings
	glViewport(0, 0, width, height);

	glutPostRedisplay(); 
}

bool Scene::checkCollision(Object* a, Object* b)
{
	if (abs(a->position.x - b->position.x) < a->size.x * a->scale.x + b->size.x * b->scale.x)
	{
		if (abs(a->position.y - b->position.y) < a->size.y * a->scale.y + b->size.y * b->scale.y)
		{
			if (abs(a->position.z - b->position.z) < a->size.z * a->scale.z + b->size.z * b->scale.z)
			{
				return true;
			}
		}
	}
	return false;
}

GLuint Scene::addTexture(char* fileName) 
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char* data;
	FILE* file;
	if (fopen_s(&file, fileName, "rb") != 0 || fread(header, 1, 54, file) != 54 || header[0] != 'B' || header[1] != 'M') return 0;
	dataPos = *(unsigned int*) & (header[0x0A]);
	imageSize = *(unsigned int*) & (header[0x22]);
	width = *(unsigned int*) & (header[0x12]);
	height = *(unsigned int*) & (header[0x16]);
	if (imageSize == 0) imageSize = width * height * 3;
	if (dataPos == 0) dataPos = 54;
	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT , GL_UNSIGNED_BYTE, data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, NULL);
	delete[] data;

	textures.push_back(textureId);
	return textureId;
}
