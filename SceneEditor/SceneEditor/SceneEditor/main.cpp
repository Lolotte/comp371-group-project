#include <Windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
int width = WIDTH;
int height = HEIGHT;

void setupMaterial(){

		float diff[4] = {1.0,0,0, 0}, spec[4]={1, 1, 1, 0};
		
		glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
		glMaterialf(GL_FRONT, GL_SHININESS, 125);

		glMaterialfv(GL_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_BACK, GL_DIFFUSE, diff);
		glMaterialf(GL_BACK, GL_SHININESS, 125);
		// the shininess factor is a number between 0 and 128, where 0 is the shiniest the object can be
}

void setupLights(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	GLfloat light_position1[] = { 0, 0, -5, 0 };
	GLfloat light1[] = { 1, 1, 1, 1 };
	GLfloat light2[] = { 0.5, 0.5, 0.5, 1.0 };

	//ambient light is reflected environmental light 
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 0 };

	// setup 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	
	glShadeModel(GL_SMOOTH);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light2);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	
	 glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

	glPopMatrix();
}

void display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glEnable(GL_DEPTH_TEST);

	// Matrix setup
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, width, height);
	glLoadIdentity();
	gluPerspective(40, (float)width / (float)height, 0.1, 1000);

	// Matrix setup
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(0, 0, -20);
	glColor3f(1, 0, 0);
	glutSolidTeapot(5);
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

void initialize(){
	setupMaterial();
	setupLights();
}

void mouse_button(int button, int state, int x, int y)
{
	//handles mouse click events
	//glutPostRedisplay();
}

void mouse_motion(int mx, int my)
{
	//handles mouse motion events
	//glutPostRedisplay();
}

void idle()
{
	//glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
}

void reshapeMainWindow(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	// GLUT initialization.
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Scene editor");
	
	// Register call backs.
	initialize();
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeMainWindow);
	glutMotionFunc(mouse_motion);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse_button);
	
	// Enter GLUT loop.
	glutMainLoop();
}