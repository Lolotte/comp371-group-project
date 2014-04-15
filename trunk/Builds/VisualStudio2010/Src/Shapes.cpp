#include <iostream>
#include <gl/glut.h>
#include <ctype.h>
#include "Shapes.h"

///////////////////////////////////////////////// class AADrawable
using namespace std;

static int shapeCounter=0;

ADrawable::ADrawable()
	: _scale(1.0, 1.0, 1.0), _angle(0), _rotation(0, 0, 0)
{
	// Constructor sets initial values.
	x = 0.0;
	y = 0.0;
	z = 0.0;
	rotating = false;
	scaling = false;
	moving = false;
	if (shapeCounter == 0)
		selected = true;
	else
		selected = false;

	shapeCounter++;
	_diffuseColor = _diffuseColor.fromFloatRGBA(0.3, 0.3, 0.3, 1.0);
	_specularColor = _specularColor.fromFloatRGBA(1.0, 1.0, 1.0, 0.0);
	_shininess = 125;
}

void ADrawable::setShininess(double shininess) {_shininess = shininess;}

void ADrawable::draw()
{
}

void ADrawable::setupMaterials()
{
	float spec[4]={_specularColor.getFloatRed(),_specularColor.getFloatGreen(),
				_specularColor.getFloatBlue(), _specularColor.getFloatAlpha()};
	float diff[4] = {_diffuseColor.getFloatRed(),_diffuseColor.getFloatGreen(),
				_diffuseColor.getFloatBlue(), _diffuseColor.getFloatAlpha()};

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shininess);
}

void ADrawable::setupMaterials(MaterialType type, Colour color)
{
	if (type == MaterialType::DIFFUSE)
		_diffuseColor = color;
	else if (type == MaterialType::SPECULAR)
		_specularColor = color;
}


void ADrawable::resetMaterials()
{
	float diff[4] = {0.3,0.3,0.3, 1.0}, spec[4]={1, 1, 1, 0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shininess);
}

void ADrawable::move(Vector3<GLfloat> const& dir)
{
	this->x += dir.x;
	this->y += dir.y;
	this->z += dir.z;
}

void ADrawable::rotate(GLfloat angle, Vector3<GLfloat> const& rotation)
{
	_angle = angle;
	_rotation = rotation;
}

void ADrawable::scale(int y){
	if (y > 0)
	{
		_scale.x -= 0.01f;
		_scale.y -= 0.01f;
		_scale.z -= 0.01f;
	}
	else
	{
		_scale.x += 0.01f;
		_scale.y += 0.01f;
		_scale.z += 0.01f;
	}

}


///////////////////////////////////////////////// class Sphere

void Sphere::draw() {
	glPushMatrix();
	//glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glRotatef(_angle, _rotation.x, _rotation.y, _rotation.z);
	glScalef(_scale.x,_scale.y, _scale.z);
	glutSolidSphere(4,100,100);
	glPopMatrix();
}


///////////////////////////////////////////////// class Cone

void Cone::draw() {
	glPushMatrix();
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glRotatef(_angle, _rotation.x, _rotation.y, _rotation.z);
	glScalef(_scale.x,_scale.y, _scale.z);
	glutSolidCone(1.5, 3, 100, 100);
	glPopMatrix();
}
///////////////////////////////////////////////// class Teapot


void Teapot::draw() {
	glPushMatrix();
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glRotatef(_angle, _rotation.x, _rotation.y, _rotation.z);
	glScalef(_scale.x,_scale.y, _scale.z);
	glFrontFace(GL_CW);
	glutSolidTeapot(3);
	glFrontFace(GL_CCW);
	glPopMatrix();
}
///////////////////////////////////////////////// class Torus

void Torus::draw() {
	glPushMatrix();
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glRotatef(_angle, _rotation.x, _rotation.y, _rotation.z);
	glScalef(_scale.x,_scale.y, _scale.z);
	glutSolidTorus(0.9, 1.1, 100, 100);
	glPopMatrix();
}

///////////////////////////////////////////////// class Tetrahedron

void Tetrahedron::draw() {
	glPushMatrix();
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glRotatef(_angle, _rotation.x, _rotation.y, _rotation.z);
	glScalef(_scale.x,_scale.y, _scale.z);
	glutSolidTetrahedron();
	glPopMatrix();
}
///////////////////////////////////////////////// class Cube

void Cube::draw() {
	glPushMatrix();
	glTranslatef(0, 0, -10);
	glTranslatef(x, y, z);
	glRotatef(_angle, _rotation.x, _rotation.y, _rotation.z);
	glScalef(_scale.x,_scale.y, _scale.z);
	glutSolidCube(2);
	glPopMatrix();
}