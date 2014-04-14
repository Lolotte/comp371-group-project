#pragma once
#include <cstdlib>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "DataStructures.hpp"

class Jittering
{
public:
	Jittering(void);
	~Jittering(void);

	void accPerspective(GLdouble fovy, GLdouble aspect, 
						GLdouble Near, GLdouble Far, GLdouble pixdx, GLdouble pixdy, 
						GLdouble eyedx, GLdouble eyedy, GLdouble focus);

	void accFrustum(GLdouble left, GLdouble right, GLdouble bottom,
					GLdouble top, GLdouble Near, GLdouble Far, GLdouble pixdx, 
					GLdouble pixdy, GLdouble eyedx, GLdouble eyedy, 
					GLdouble focus);

	static int MAX_ITERATIONS;
	static const double PI_;
};

const Vector2<double> JITTER1[] = {Vector2<double>(0.5, 0.5)};
const Vector2<double> JITTER2[] = {Vector2<double>(0.25, 0.75), 
								  Vector2<double>(0.75, 0.25)};
const Vector2<double> JITTER3[] = {Vector2<double>(0.5033922635, 0.8317967229), 
                            Vector2<double>(0.7806016275, 0.2504380877),
                            Vector2<double>(0.2261828938, 0.4131553612)};
const Vector2<double> JITTER4[] = {Vector2<double>(0.375, 0.25), 
                            Vector2<double>(0.125, 0.75), 
                            Vector2<double>(0.875, 0.25), 
                            Vector2<double>(0.625, 0.75)};
const Vector2<double> JITTER5[] = {Vector2<double>(0.5, 0.5), 
                            Vector2<double>(0.3, 0.1), 
                            Vector2<double>(0.7, 0.9), 
                            Vector2<double>(0.9, 0.3), 
                            Vector2<double>(0.1, 0.7)};
const Vector2<double> JITTER6[] = {Vector2<double>(0.4646464646, 0.4646464646), 
                            Vector2<double>(0.1313131313, 0.7979797979),
                            Vector2<double>(0.5353535353, 0.8686868686), 
                            Vector2<double>(0.8686868686, 0.5353535353),
                            Vector2<double>(0.7979797979, 0.1313131313), 
                            Vector2<double>(0.2020202020, 0.2020202020)};
const Vector2<double> JITTER8[] = {Vector2<double>(0.5625, 0.4375), 
                            Vector2<double>(0.0625, 0.9375), 
                            Vector2<double>(0.3125, 0.6875), 
                            Vector2<double>(0.6875, 0.8125),  
                            Vector2<double>(0.8125, 0.1875), 
                            Vector2<double>(0.9375, 0.5625), 
                            Vector2<double>(0.4375, 0.0625), 
                            Vector2<double>(0.1875, 0.3125)};
const Vector2<double> JITTER9[] = {Vector2<double>(0.5, 0.5), 
                            Vector2<double>(0.1666666666, 0.9444444444), 
                            Vector2<double>(0.5, 0.1666666666), 
                            Vector2<double>(0.5, 0.8333333333), 
                            Vector2<double>(0.1666666666, 0.2777777777), 
                            Vector2<double>(0.8333333333, 0.3888888888), 
                            Vector2<double>(0.1666666666, 0.6111111111),
                            Vector2<double>(0.8333333333, 0.7222222222), 
                            Vector2<double>(0.8333333333, 0.0555555555)};
const Vector2<double> JITTER12[] = {Vector2<double>(0.4166666666, 0.625), 
                             Vector2<double>(0.9166666666, 0.875), 
                             Vector2<double>(0.25, 0.375),
                             Vector2<double>(0.4166666666, 0.125), 
                             Vector2<double>(0.75, 0.125), 
                             Vector2<double>(0.0833333333, 0.125), 
                             Vector2<double>(0.75, 0.625),
                             Vector2<double>(0.25, 0.875), 
                             Vector2<double>(0.5833333333, 0.375), 
                             Vector2<double>(0.9166666666, 0.375),
                             Vector2<double>(0.0833333333, 0.625), 
                             Vector2<double>(0.583333333, 0.875)};
const Vector2<double> JITTER16[] = {Vector2<double>(0.375, 0.4375), 
                             Vector2<double>(0.625, 0.0625), 
                             Vector2<double>(0.875, 0.1875), 
                             Vector2<double>(0.125, 0.0625), 
                             Vector2<double>(0.375, 0.6875), 
                             Vector2<double>(0.875, 0.4375), 
                             Vector2<double>(0.625, 0.5625), 
                             Vector2<double>(0.375, 0.9375), 
                             Vector2<double>(0.625, 0.3125), 
                             Vector2<double>(0.125, 0.5625), 
                             Vector2<double>(0.125, 0.8125), 
                             Vector2<double>(0.375, 0.1875), 
                             Vector2<double>(0.875, 0.9375), 
                             Vector2<double>(0.875, 0.6875), 
                             Vector2<double>(0.125, 0.3125), 
                             Vector2<double>(0.625, 0.8125)};

const Vector2<double> * const JITTER[] = {NULL, JITTER1, JITTER2, JITTER3,
										   JITTER4, JITTER5, JITTER6, NULL, JITTER8, JITTER9,
										   NULL, NULL, JITTER12, NULL, NULL, NULL, JITTER16};

