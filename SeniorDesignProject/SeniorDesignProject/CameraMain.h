
#ifndef CAMERA_H
#define CAMERA_H

//#include <windows.h>
#include <d3d11.h>
//#include <d3dx11.h>
//#include <d3dx10.h>
#include <xnamath.h>

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
	void setCamProjection(float x, float y, float z, float w);

	XMVECTOR getCamPosition();
	void setCamPosition(float x, float y, float z, float w);
	XMVECTOR getCamTarget();
	void setCamTarget(float x, float y, float z, float w);
	XMVECTOR getCamUp();
	void setCamUp(float x, float y, float z, float w);

	void setDefaultForward(float x, float y, float z, float w);
	XMVECTOR getDefaultForward();
	void setDefaultRight(float x, float y, float z, float w);
	XMVECTOR getDefaultRight();
	void setCamForward(float x, float y, float z, float w);
	XMVECTOR getCamForward();
	void setCamRight(float x, float y, float z, float w);
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

private:

	XMMATRIX WVP;
	XMMATRIX World;
	XMMATRIX camView;
	XMMATRIX camProjection;

	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;
	XMVECTOR DefaultForward;
	XMVECTOR DefaultRight;
	XMVECTOR camForward;
	XMVECTOR camRight;

	XMMATRIX camRotationMatrix;

	float moveLeftRight;
	float moveBackForward;

	float camYaw;
	float camPitch;
};

#endif // CAMERA_H
