#include "Jittering.h"
#include <gl/glut.h>
#include <cmath>

const double Jittering::PI_ = 3.14159265358979323846;
int Jittering::MAX_ITERATIONS = 15;

Jittering::Jittering(void)
{
}


Jittering::~Jittering(void)
{
}


void Jittering::accFrustum(GLdouble left, GLdouble right, GLdouble bottom,
							GLdouble top, GLdouble Near, GLdouble Far, GLdouble pixdx, 
							GLdouble pixdy, GLdouble eyedx, GLdouble eyedy, 
							GLdouble focus)
{
    GLdouble xwsize, ywsize; 
    GLdouble dx, dy;
    GLint viewport[4];

    glGetIntegerv (GL_VIEWPORT, viewport);

    xwsize = right - left;
    ywsize = top - bottom;
	
	dx = -(pixdx*xwsize/(GLdouble) viewport[2] + eyedx*Near / focus);
    dy = -(pixdy*ywsize/(GLdouble) viewport[3] + eyedy*Near/focus);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum (left + dx, right + dx, bottom + dy, top + dy, Near, Far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (-eyedx, -eyedy, 0.0);
}

void Jittering::accPerspective(GLdouble fovy, GLdouble aspect, 
								GLdouble Near, GLdouble Far, GLdouble pixdx, GLdouble pixdy, 
								GLdouble eyedx, GLdouble eyedy, GLdouble focus)
{
    GLdouble fov2,left,right,bottom,top;
    fov2 = ((fovy*PI_) / 180.0) / 2.0;

    top = Near / (cos(fov2) / sin(fov2));
    bottom = -top;
    right = top * aspect;
    left = -right;

    accFrustum (left, right, bottom, top, Near, Far,
        pixdx, pixdy, eyedx, eyedy, focus);
}
