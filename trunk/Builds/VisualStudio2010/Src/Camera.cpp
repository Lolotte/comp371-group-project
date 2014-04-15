#include <Windows.h>
#include <gl\glut.h>
#include "camera.h"
#include "math.h"
#include <iostream>


Camera::Camera()
	: _viewDir(0.0, 0.0, -1.0), _viewDirChanged(false)
{
}

void Camera::getViewDir( void )
{
	Vector3<GLfloat> Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos( (_rotation.y + 90.0) * PIdiv180);
	Step1.z = -sin( (_rotation.y + 90.0) * PIdiv180);
	//Rotate around X-axis:
	double cosX = cos (_rotation.x * PIdiv180);
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(_rotation.x * PIdiv180);
	
	// not implemented yet
	_viewDir = Step2;
}
void Camera::move (Vector3<GLfloat> & dir)
{
	_position.add(dir);
}

void Camera::rotateY (GLfloat Angle)
{
	_rotation.y += Angle;
	_viewDirChanged = true;
}

void Camera::rotateX (GLfloat Angle)
{
	_rotation.x += Angle;
	_viewDirChanged = true;
}

void Camera::render( void )
{
	glRotatef(-_rotation.x , 1.0, 0.0, 0.0);
	glRotatef(-_rotation.y , 0.0, 1.0, 0.0);
	glRotatef(-_rotation.z , 0.0, 0.0, 1.0);
	glTranslatef( -_position.x, -_position.y, -_position.z );
}

void Camera::moveForwards( GLfloat Distance )
{
	if (_viewDirChanged)
		getViewDir();

	Vector3<GLfloat> moveVector;
	moveVector.x = _viewDir.x * -Distance;
	moveVector.y = _viewDir.y * -Distance;
	moveVector.z = _viewDir.z * -Distance;
	_position.add(moveVector);
}

void Camera::strafeRight ( GLfloat Distance )
{
	if (_viewDirChanged)
		getViewDir();
	Vector3<GLfloat> moveVector;
	moveVector.z = -_viewDir.x * -Distance;
	moveVector.y = 0.0;
	moveVector.x = _viewDir.z * -Distance;
	_position.add(moveVector);
}