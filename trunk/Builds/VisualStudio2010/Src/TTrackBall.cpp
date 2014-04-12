
#include "TTrackBall.h"
#include <math.h>

#include <GL/glut.h>

#define RADIUS .25
#define M_PI 3.141592654

TTrackBall::TTrackBall()
    :scrWidth(0), scrHeight(0){

    pivot_point = TPoint(0, 0, 0);
    reset();
}


TTrackBall::TTrackBall(int width, int height)
:scrWidth(width), scrHeight(height){
    pivot_point = TPoint(0, 0, 0);
    reset();
}

TTrackBall::TTrackBall(const TTrackBall& T){
    track_matrix = T.track_matrix;
    pivot_point = T.pivot_point;
    scrWidth = T.scrWidth;
    scrHeight = T.scrHeight;
}


TTrackBall& TTrackBall::operator=(const TTrackBall& T){
    track_matrix = T.track_matrix;
    pivot_point = T.pivot_point;
    scrWidth = T.scrWidth;
    scrHeight = T.scrHeight;
    return *this;
}


void TTrackBall::Resize(int width, int height ){
    
    scrWidth = width;
    scrHeight = height;
}


void TTrackBall::reset(){
    track_matrix.setIdentity();
}

void TTrackBall::track(TPoint old_p, TPoint new_p, float scale){
    TMatrix4x4 m;
    float fx, fy, fz;

    // call the track ball code
    vGenerateRotVec(old_p[0], old_p[1], new_p[0], new_p[1], 
		    fx, fy, fz);
			
    // generate the matrix
    vRotateScene(fx, fy, fz, scale, m);
	
    TPoint newP;
    newP =  track_matrix*pivot_point;

    // rotate around arbitrary point (pivot_point in this case)
    track_matrix =  TTranslate( -newP[0], -newP[1], -newP[2]) *  track_matrix;
		
    // multiply the matrix
    track_matrix = m *  track_matrix;
    
    // around an arbitrary point ch 2
    track_matrix =  TTranslate( newP[0], newP[1], newP[2]) *  track_matrix;
}


TMatrix4x4& TTrackBall::getMatrix(){
    return track_matrix;
}
  
 /*
 * Name      : void vRotateScene(float fVecX, float fVecY, float fVecZ, 
 *                               Matrix mNewMat)
 *
 * Parameters: float  fVecX   - The X component of the rotation vector.
 *             float  fVecY   - The Y component of the rotation vector.
 *             float  fVecZ   - The Z component of the rotation vector.
 *             Matrix mNewMat - The matrix to store the rotation in.
 *
 * Returns   : void
 *
 * Purpose   : Generates a matrix based on a rotation vector.
 */
void TTrackBall::vRotateScene(float fVecX, float fVecY, float fVecZ, 
float fScale,   TMatrix4x4& mNewMat,TMatrix4x4*  mInvMat)
{
    
    float fRadians, fInvLength, fNewVecX, fNewVecY, fNewVecZ;

    fVecX *= -1.0;
    fVecY *= -1.0;
    
    // the scale from pick
    fScale = fScale * 180.0 / M_PI;

    /* 
     * Find the length of the vector.
     */
    fRadians = sqrt(fVecX * fVecX + fVecY * fVecY + fVecZ * fVecZ);

    /*  
     * If the vector has zero length - return the identity matrix.
     */
    if (fRadians > -0.000001 && fRadians < 0.000001) {
        mNewMat.setIdentity();
        return;
    }

    /* 
     * Normalize the rotation vector.
     */
    fInvLength = 1 / fRadians;
    fNewVecX   = fVecX * fInvLength;
    fNewVecY   = -fVecY * fInvLength;
    fNewVecZ   = fVecZ * fInvLength;
    fRadians  *= fScale;  

    /*
     * Use OpenGL to rotate about an arbitrary axis
     */
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(fRadians, fNewVecX, fNewVecY, fNewVecZ);
    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)mNewMat.getBuffer());
    glPopMatrix();

    // inverse matrix
    if(mInvMat){
	glPushMatrix();
	glLoadIdentity();
	glRotatef(-fRadians, fNewVecX, fNewVecY, fNewVecZ);
	float mm[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mm);//(GLfloat *)mInvMat->getBuffer());
	glPopMatrix();
    }

}

/*
 * Name      : void vGenerateRotVec(float fCurrentX, float fCurrentY, 
 *                                  float *fVecX, float *fVecY, float *fVecZ)
 *
 * Parameters: float fOldX
 			   float fOldY
 			   float fCurrentX - The current X location of the cursor.
 *             float fCurrentY - The current Y location of the cursor.
 *             float *fVecX    - The X component of the rotation vector.
 *             float *fVecY    - The Y component of the rotation vector.
 *             float *fVecZ    - The Z component of the rotation vector.
 *
 * Returns   : void
 *
 * Purpose   : Computes a rotation vector for the trackball
 *             interaction.
 */
void TTrackBall::vGenerateRotVec(float fOldX, float fOldY, 
					float fCurrentX, float fCurrentY, float& fVecX,
                     float& fVecY, float& fVecZ) {

    long  nXOrigin, nYOrigin;
    float fNewX, fNewY, fNewZ, fLength;
    float fLastX, fLastY, fLastZ;
    int nWinWidth, nWinHeight, nEdge;

    /*
     * Compute center of window.
     */
    
    nWinWidth = scrWidth;
    nWinHeight = scrHeight;
    if(scrWidth>scrHeight)
	nEdge = scrHeight;
    else
	nEdge = scrWidth;
   		
   
    
    nXOrigin = nWinWidth / 2;
    nYOrigin = nWinHeight / 2;

    /*
     * Calculate components.
     */
    fNewX    = (fCurrentX - (float)nXOrigin) * 2.0 / (float)nEdge;
    fNewY    = (fCurrentY - (float)nYOrigin) * 2.0 / (float)nEdge;
    fNewZ    = (RADIUS - fNewX * fNewX - fNewY * fNewY);
   
   fLastX    = (fOldX - (float)nXOrigin) * 2.0 / (float)nEdge;
   fLastY    = (fOldY - (float)nYOrigin) * 2.0 / (float)nEdge;
   fLastZ    = (RADIUS - fLastX * fLastX - fLastY * fLastY);

   /*
    * Moving around outside of window.
    */

	if (fLastZ < 0.0) {
      fLength = sqrt(1.0 - fLastZ);
      fLastZ  = 0.0;
      fLastX /= fLength;
      fLastY /= fLength;
   } else {
      fLastZ = sqrt(fLastZ);
   }


	if (fNewZ < 0.0) {
      fLength = sqrt(1.0 - fNewZ);
      fNewZ  = 0.0;
      fNewX /= fLength;
      fNewY /= fLength;
   	} else {
      fNewZ = sqrt(fNewZ);
    }


   /*
    * Generate rotation vector.
    */
   fVecX = fLastY * fNewZ - fNewY * fLastZ;
   fVecY = fLastZ * fNewX - fNewZ * fLastX;
   fVecZ = -(fLastX * fNewY - fNewX * fLastY);

   /*
    * Update for next time.
    */
   fLastX = fNewX;
   fLastY = fNewY;
   fLastZ = fNewZ;
}
  
