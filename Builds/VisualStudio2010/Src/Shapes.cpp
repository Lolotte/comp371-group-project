#include <iostream>
#include <gl/glut.h>
#include <ctype.h>
#include "Shapes.h"
#include "TTrackBall.h"
#include "TTuple.h"

///////////////////////////////////////////////// class AADrawable
using namespace std;

static int shapeCounter=0;

ADrawable::ADrawable()
	: _scale(1.0, 1.0, 1.0)
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
	glMultMatrixf((float*) view.getBuffer());
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

void ADrawable::move(int x, int y) {
	float deltay = ((float) (x)) * 0.01;
	float deltax = ((float) (y)) * 0.01;
	//glPushMatrix();
	this->x += deltax;
	this->y += deltay;
	//glTranslatef(x + deltax, y + deltay, 0);
}

void ADrawable::rotate(int mx, int my) {
	glPushMatrix();
	glTranslatef(-x, -y, -z);
	glRotatef(1, 1, 1, 1);
	glTranslatef(x, y, z);
	cout << "rotating " << endl;
}

void ADrawable::scale(int y){

	/*float factor = 0.5;
	factor = 0.005;
	float delta = ((float) (y)) * factor;
	w *= 1.005*delta;
	h *= delta;*/
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
	glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glutSolidSphere(4,100,100);
	glPopMatrix();
}


///////////////////////////////////////////////// class Cone

void Cone::draw() {
	glPushMatrix();
	glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glutSolidCone(1.5, 3, 100, 100);
	glPopMatrix();
}
///////////////////////////////////////////////// class Teapot


void Teapot::draw() {
	glPushMatrix();
	glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glScalef(_scale.x,_scale.y, _scale.z);
	glFrontFace(GL_CW);
	glutSolidTeapot(3);
	glFrontFace(GL_CCW);
	glPopMatrix();
}
///////////////////////////////////////////////// class Torus

void Torus::draw() {
	glPushMatrix();
	glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glutSolidTorus(0.9, 1.1, 100, 100);
	glPopMatrix();
}

///////////////////////////////////////////////// class Tetrahedron

void Tetrahedron::draw() {
	glPushMatrix();
	glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glutSolidTetrahedron();
	glPopMatrix();
}
///////////////////////////////////////////////// class Cube

void Cube::draw() {
	glPushMatrix();
	glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -10);
	glRotatef(45, 0, 1, 0);
	glTranslatef(x, y, z);
	glutSolidCube(2);
	glPopMatrix();
}