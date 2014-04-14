#ifndef Shapes_h
#define Shapes_h
#include "TTrackBall.h"
#include "TTuple.h"
#include "..\..\JuceLibraryCode\JuceHeader.h"

class ADrawable {
	// An abstract class for objects that can be drawn.

public:
	enum MaterialType {SPECULAR, DIFFUSE};

	ADrawable();
	virtual ~ADrawable() {}
	//virtual void dokey(int key);
	virtual void move(int x, int y);
	virtual void rotate(int mx, int my);
	virtual void scale(int y);
	virtual void draw();
	void setShininess(double);
	virtual void setupMaterials();
	virtual void setupMaterials(MaterialType type, Colour diffuseColor);
	void resetMaterials();

	bool selected;		// Selected object receives keystrokes.
	bool rotating;
	bool scaling;
	bool moving;


protected:
	Colour _diffuseColor;
	Colour _specularColor;
	double _shininess;
	TMatrix4x4 view;
	TTrackBall ball;	// Trackball used to rotate the object
	char num;			// Object's name.
	GLfloat x, y, z, w, h;	// Object's position and dimensions.
};

class Sphere : public ADrawable {
public:
	Sphere(): ADrawable() {
		r = 0.8f;
		g = 0.0f;
		b = 0.4f;
		drawCount = 0;
	}
	void draw();
	int drawCount; 

private:
	GLfloat r, g, b;	// Colour components for sphere.

};

class Cone : public ADrawable {
public:
	Cone(): ADrawable() {
		r = 0.8f;
		g = 0.0f;
		b = 0.4f;
		drawCount = 0;
	}
	void draw();
	int drawCount; 
private:
	GLfloat r, g, b;

};

class Teapot : public ADrawable {
public:
	Teapot() : ADrawable() {
		r = 0.8f;
		g = 0.0f;
		b = 0.4f;
		drawCount = 0;
	}
	void draw();
	int drawCount;

private:
	GLfloat r, g, b;

};

class Torus : public ADrawable {
public:
	Torus() : ADrawable() {
		r = 0.8f;
		g = 0.0f;
		b = 0.4f;
		drawCount = 0;
	}
	void draw();
	int drawCount;
private:
	GLfloat r, g, b;

};

class Tetrahedron : public ADrawable {
public:
	Tetrahedron() : ADrawable() {
		r = 0.8f;
		g = 0.0f;
		b = 0.4f;
		drawCount = 0;
	}
	void draw();
	int drawCount;
private:
	GLfloat r, g, b;

};

class Cube : public ADrawable {
public:
	Cube() : ADrawable() {
		r = 0.8f;
		g = 0.0f;
		b = 0.4f;
		drawCount = 0;
	}
	void draw();
	int drawCount;

private:
	GLfloat r, g, b;

};

#endif