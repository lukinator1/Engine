#include "Camera.h"
Camera::~Camera()
{
}
float Camera::fov = 70.0f;
float Camera::maxviewdistance = 1000.0f;
float Camera::minviewdistance = 0.1f;
float Camera::aspectratiowidth = 800.0f;
float Camera::aspectratioheight = 600.0f;
bool Camera::orthographicprojection = false;
vector3 Camera::cameraposition(0.0f, 0.0f, 0.0f);
/*vector3 Camera::forwardvector(0.0f, 0.0f, 1.0f);
vector3 Camera::upvector(0.0f, 1.0f, 0.0f);*/
Quaternion Camera::camerarotation(0.0f, 0.0f, 0.0f, 1.0f);
