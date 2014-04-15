#pragma once
#include "DataStructures.hpp"
#include "Shapes.h"

class Arcball
{
public:
	Arcball(void);
	~Arcball(void);

	void rotateAccToArcball(int mx, int my, ADrawable* selectedObject);
	void setMouse(int, int);

private:
	float minF(float a, float b);
	
	Vector3<GLfloat> GetArcballVector(int x, int y);
	
	float _angle;
	int _mouseX;
	int _mouseY;
	Vector3<GLfloat> _axis;
};

