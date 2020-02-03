#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}
float Camera::fov = 70.0f;
float Camera::maxviewdistance = 1000.0f;
float Camera::minviewdistance = 0.1f;
float Camera::aspectratiowidth = 800.0f;
float Camera::aspectratioheight = 600.0f;
bool Camera::orthographicprojection = false;
