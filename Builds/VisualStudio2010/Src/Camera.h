
#include "DataStructures.hpp"
#define PI 3.1415265359
#define PIdiv180 3.1415265359/180.0


/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

class Camera
{
public:
	Camera();				
	void render ( void );	
							
	void move ( Vector3<float> & Direction );
	void rotateX ( float Angle );
	void rotateY ( float Angle );
	void rotateZ ( float Angle );
	void rotateXYZ ( Vector3<float>& Angles );
	void moveForwards ( float Distance );
	void strafeRight ( float Distance );

private:
	void getViewDir ( void );

	Vector3<float> _position;
	Vector3<float> _viewDir;		
	bool _viewDirChanged;
	Vector3<float> _rotation;	
};

