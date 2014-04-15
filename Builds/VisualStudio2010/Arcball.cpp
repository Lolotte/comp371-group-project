#include "Arcball.h"

Arcball::Arcball(void)
	: _angle(0), _mouseX(0), _mouseY(0), _axis(0, 0, 0)
{
}


Arcball::~Arcball(void)
{
}

void Arcball::setMouse(int x, int y)
{
	_mouseX = x;
	_mouseY = y;
}

float Arcball::minF(float a, float b)
{
	return a < b ? a : b;
}

Vector3<GLfloat> Arcball::GetArcballVector(int x, int y)
{
	GLint viewport[4] = {0, 0, 850, 768};
	Vector3<GLfloat> p;
	p.x = 1.0 * (float)x / viewport[2] * 2.0 - 1.0;
	p.y = 1.0 * (float)y / viewport[3] * 2.0 - 1.0;
	p.y *= -1;
	p.z = 0;

	float pToCenter = p.x * p.x + p.y * p.y; // p.z is 0 so no need to add it
	if (pToCenter <= 1) // pythagore
		p.z = sqrt(1 - pToCenter);
	else // get the nearest point
		p.normalize();
	return p;
}

void Arcball::rotateAccToArcball(int mx, int my, ADrawable* selectedObject)
{
	Vector3<GLfloat> u = GetArcballVector(_mouseX, _mouseY);
	Vector3<GLfloat> v = GetArcballVector(mx, my);
	
	float dotProduct = u.dot(v);
	float aCos = acosf(minF(1.0f, dotProduct));
	_angle += aCos * 180.0f / 3.14f;
	int a = (int)_angle % 360;
	_angle = a;
	_angle *= 0.8f; // to slow down the rotation
	Vector3<GLfloat> axisInCameraCoord = u.cross(v);

	_axis.x = axisInCameraCoord.x;
	_axis.y = axisInCameraCoord.y;
	_axis.z = axisInCameraCoord.z;
	if (selectedObject != NULL)
		selectedObject->rotate(_angle, _axis);
}

