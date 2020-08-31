#pragma once
#include <vector>
#include "Vector3f.h"
#include "Vector4f.h"
#include "Object.h"
#include "Light.h"
#include "Camera.h"

using namespace std;

class Scene
{
public:
	Scene(const char* windowCaption, int windowPosX, int windowPosY, int windowWidth, int windowHeight);
	~Scene();

	void setFullScreen(bool fullScreen);
	void setKeyboardFunction(void (*keyboardFunction)(Scene* scene, unsigned char key, int mouseX, int mouseY));
	void setSpecialFunction(void (*specialFunction)(Scene* scene, int key, int mouseX, int mouseY));
	void setMouseButtonFunction(void (*mouseButtonFunction)(Scene* scene, int button, int state, int mouseX, int mouseY));
	void setMouseMoveActiveFunction(void (*mouseMoveActiveFunction)(Scene* scene, int mouseX, int mouseY));
	void setMouseMovePassiveFunction(void (*mouseMovePassiveFunction)(Scene* scene, int mouseX, int mouseY));
	void setFrameRate(int fps);
	int getWidth();
	int getHeight();
	bool isFullScreen();
	GLuint addTexture(char* fileName);
	void addObject(Object* object);
	void start();

	bool fullScreen;
	Camera camera;
	Vector3f backgroundColor;
	Vector4f lightAmbient;
	Light light[8];
	
	vector<Object*> objects;
	vector<GLuint> textures;
	GLUquadricObj* quadric; // Quadric variable (gluSphere itp)
	GLint quadricParts;
	
private:

	static Scene* instance;

	int windowHandle;
	int windowPosX, windowPosY;
	int windowWidth, windowHeight;
	int renderInterval;

	void (*keyboardFunction)(Scene* scene, unsigned char key, int mouseX, int mouseY);
	void (*specialFunction)(Scene* scene, int _cChar, int mouseX, int mouseY);
	static void glutKeyboardFunction(unsigned char key, int mouseX, int mouseY);
	static void glutSpecialFunction(int key, int mouseX, int mouseY);

	void (*mouseButtonFunction)(Scene* scene, int button, int state, int mouseX, int mouseY);
	void (*mouseMoveActiveFunction)(Scene* scene, int mouseX, int mouseY);
	void (*mouseMovePassiveFunction)(Scene* scene, int mouseX, int mouseY);
	static void glutMouseButtonFunction(int button, int state, int mouseX, int mouseY);
	static void glutMouseMoveActiveFunction(int mouseX, int mouseY);
	static void glutMouseMovePassiveFunction(int mouseX, int mouseY);

	static void glutRenderFunction();
	static void glutReshapeFunction(int width, int height);
	static void glutTimerFunction(int sceneCallback);
	void resize(int width, int height);
	void render();
	bool checkCollision(Object* a, Object* b);

};
