#include <iostream>
#include <gl/glut.h>
#include <ctype.h>
#include "Shapes.h"
#include "TTrackBall.h"
#include "TTuple.h"

///////////////////////////////////////////////// class AADrawable
using namespace std;
ADrawable::ADrawable() {
	// Constructor sets initial values.
	x = 5.0;
	y = 0.0;
	z = -20.0;
	rotating = false;
	scaling = false;
	moving = false;
	glMultMatrixf((float*) view.getBuffer());
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
	// Move the object to its current position.
	float deltay = ((float) (x)) * 0.01;
	float deltax = ((float) (y)) * 0.01;
	glPushMatrix();
	glTranslatef(deltax, deltay, 0);
	cout << "moving " << endl;
}

void ADrawable::rotate(int cx, int cy, int mx, int my) {
	ball.track(TPoint(cx, cy), TPoint(mx,my));
	cout << "rotating " << endl;
}

void ADrawable::scale(int y){
	glPushMatrix();
	float factor = 0.5;
	factor = 0.005;
	float delta = ((float) (y)) * factor;
	glScalef(1.005*delta,delta, 1);
	glPushMatrix();
	cout << "scaling " << endl;
}


///////////////////////////////////////////////// class Sphere

void Sphere::draw() {
	glPushMatrix();
	glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(0, 2, -20);
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
	glTranslatef(-5, -2, -20);
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
	glTranslatef(0, -3, -20);
	glFrontFace(GL_CW);
	glutSolidTeapot(3);
	glFrontFace(GL_CCW);
	glPopMatrix();
}
///////////////////////////////////////////////// class Torus

void Torus::draw() {
	glPushMatrix();
	//glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(-5, -2, -20);
	glutSolidTorus(3, 4, 100, 100);
	glPopMatrix();
}

///////////////////////////////////////////////// class Tetrahedron

void Tetrahedron::draw() {
	glPushMatrix();
	//glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(-5, -2, -20);
	glutSolidTetrahedron();
	glPopMatrix();
}
///////////////////////////////////////////////// class Cube

void Cube::draw() {
	glPushMatrix();
	//glMultMatrixf((float*) ball.getMatrix().getBuffer());
	glTranslatef(-5, -2, -20);
	glutSolidCube(2);
	glPopMatrix();
}