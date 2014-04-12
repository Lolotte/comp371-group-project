#ifndef _T_TRACK_BALL_H_
#define _T_TRACK_BALL_H_

#define MAGIC_SCALE 4.3

#include "TTuple.h"
#include <math.h>
#include <stdlib.h>

//using namespace T3D

class TTrackBall {
  public:

    TTrackBall();
    TTrackBall(int width, int height);

    // copy constructor and assignment operator
    TTrackBall(const TTrackBall&);
    TTrackBall& operator=(const TTrackBall&);

    void Resize(int width, int height);
    void track(TPoint old_p, TPoint new_p, float scale = MAGIC_SCALE);
    TMatrix4x4& getMatrix();
    
    void reset();

  public:

    // from the old cs488 code
    void vRotateScene(float, float, float, float, TMatrix4x4&, TMatrix4x4* m =NULL);
    void vGenerateRotVec(float ,float  ,float, float, float&, float&, float&);

    TMatrix4x4 track_matrix;
    TPoint pivot_point;
    int scrWidth, scrHeight;
};

#endif // _T_TRACK_BALL_H_
