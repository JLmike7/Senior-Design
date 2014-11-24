#ifndef CAMERA_H
#define CAMERA_H

#include <d3d11.h>
#include <xnamath.h>
#include "Point.h"

class CameraMain
{
public:
	CameraMain();
	~CameraMain();

	XMMATRIX getWVP();
	void setWVP(const XMMATRIX &_world, const XMMATRIX &_camView, const XMMATRIX &_camProjection);
	XMMATRIX getWorld();
	void setWorld();
	XMMATRIX getCamView();
	void setCamView(XMVECTOR camPosition, XMVECTOR camTarget, XMVECTOR camUp);
	XMMATRIX getCamProjection();
	void setCamProjection(float a, float b, float c, float d);

	XMVECTOR getCamPosition();
	Point getsCamPosition();
	void setCamPosition(float a, float b, float c, float d);
	XMVECTOR getCamTarget();
	Point getsCamTarget();
	void setCamTarget(float a, float b, float c, float d);
	XMVECTOR getCamUp();
	Point getsCamUp();
	void setCamUp(float a, float b, float c, float d);

	///////////////**************new**************////////////////////

	void setDefaultForward(float a, float b, float c, float d);
	XMVECTOR getDefaultForward();
	void setDefaultRight(float a, float b, float c, float d);
	XMVECTOR getDefaultRight();
	void setCamForward(float a, float b, float c, float d);
	XMVECTOR getCamForward();
	void setCamRight(float a, float b, float c, float d);
	XMVECTOR getCamRight();

	void setMoveLeftRight(float a);
	float getMoveLeftRight();
	void setMoveBackForward(float a);
	float getMoveBackForward();

	void setCamYaw(float a);
	float getCamYaw();
	void setCamPitch(float a);
	float getCamPitch();

	void UpdateCamera();
	///////////////**************new**************////////////////////

private:
	XMMATRIX WVP;
	XMMATRIX World;
	XMMATRIX camView;
	XMMATRIX camProjection;

	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;
	///////////////**************new**************////////////////////
	XMVECTOR DefaultForward;
	XMVECTOR DefaultRight;
	XMVECTOR camForward;
	XMVECTOR camRight;

	XMMATRIX camRotationMatrix;

	float moveLeftRight;
	float moveBackForward;

	float camYaw;
	float camPitch;
	///////////////**************new**************////////////////////
};

#endif // CAMERA_H
