#include "Camera.h"

void Camera::update()
{
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, 0, 1, 0);
}
