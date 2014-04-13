#include <iostream>
#include <gl/glut.h>
#include <ctype.h>
#include "Shapes.h"
#include "TTrackBall.h"
#include "TTuple.h"

///////////////////////////////////////////////// class AADrawable
using namespace std;

static int shapeCounter=0;

ADrawable::ADrawable() {
	// Constructor sets initial values.
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 1.0;
	h = 1.0;
	rotating = false;
	scaling = false;
	moving = false;
	if (shapeCounter == 0)
		selected = true;
	else
		selected = false;
	glMultMatrixf((float*) view.getBuffer());
	shapeCounter++;
}

void ADrawable::draw()
{
}

void ADrawable::setupMaterials()
{
	float diff[4] = {1.0,1.0,1.0, 1.0}, spec[4]={1, 1, 1, 0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 125);
}

void ADrawable::move(int x, int y) {
	
	float deltay = ((float) (x)) * 0.01;
	float deltax = ((float) (y)) * 0.01;
	glPushMatrix();
	x += deltax;
	y += deltay;
	glTranslatef(x, y, 0);
}

void ADrawable::rotate(int mx, int my) {
	glPushMatrix();
	glTranslatef(-x, -y, -z);
	glRotatef(1, 1, 1, 1);
	glTranslatef(x, y, z);
	cout << "rotating " << endl;
}

void ADrawable::scale(int y){
	glPushMatrix();
	float factor = 0.5;
	factor = 0.005;
	float delta = ((float) (y)) * factor;
	w *= 1.005*delta;
	h *= delta;
	glScalef(w,h, 1);
	glPushMatrix();
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

void Sphere::setupMaterials()
{
	float diff[4] = {0,1,0, 1.0}, spec[4]={1, 1, 1, 0};
	//float ambient[4] = {0.5, 0.5, 0.5, 0.5};

//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 125);
}

///////////////////////////////////////////////// class Cone

void Cone::draw() {
	glPushMatrix();
	//glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glutSolidCone(1.5, 3, 100, 100);
	glPopMatrix();
}
///////////////////////////////////////////////// class Teapot

void Teapot::setupMaterials()
{
	float diff[4] = {1.0,0,0, 1.0}, spec[4]={1, 1, 1, 0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 125);
}

void Teapot::draw() {
	glPushMatrix();
	//glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glFrontFace(GL_CW);
	glutSolidTeapot(3);
	glFrontFace(GL_CCW);
	glPopMatrix();
}
///////////////////////////////////////////////// class Torus

void Torus::draw() {
	glPushMatrix();
	//glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glutSolidTorus(0.9, 1.1, 100, 100);
	glPopMatrix();
}

///////////////////////////////////////////////// class Tetrahedron

void Tetrahedron::draw() {
	glPushMatrix();
	//glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -20);
	glTranslatef(x, y, z);
	glutSolidTetrahedron();
	glPopMatrix();
}
///////////////////////////////////////////////// class Cube

void Cube::setupMaterials()
{
	float diff[4] = {1.0,1.0,0, 1.0}, spec[4]={1, 1, 1, 0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 125);
}

void Cube::draw() {
	glPushMatrix();
	//glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 0, -10);
	glRotatef(45, 0, 1, 0);
	glTranslatef(x, y, z);
	glutSolidCube(2);
	glPopMatrix();
}