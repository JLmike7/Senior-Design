//***************************************************************************************
// CameraMain.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "CameraMain.h"

CameraMain::CameraMain(){
}

CameraMain::~CameraMain()
{
}

XMMATRIX CameraMain::getWVP()
{
	return WVP;
}

void CameraMain::setWVP(const XMMATRIX &_world, const XMMATRIX &_camView, const XMMATRIX &_camProjection)
{
	WVP = _world * _camView * _camProjection;
}

XMMATRIX CameraMain::getWorld()
{
	return World;
}

void CameraMain::setWorld()
{
	World = XMMatrixIdentity();
}

XMMATRIX CameraMain::getCamView()
{
	return camView;
}

void CameraMain::setCamView(XMVECTOR camPosition, XMVECTOR camTarget, XMVECTOR camUp)
{
	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
}

XMMATRIX CameraMain::getCamProjection()
{
	return camProjection;
}

void CameraMain::setCamProjection(float a, float b, float c, float d)
{
	//camProjection = XMMatrixPerspectiveFovLH( 0.4f*3.14f, Width/Height, 1.0f, 1000.0f);
	camProjection = XMMatrixPerspectiveFovLH(a, b, c, d);
}


XMVECTOR CameraMain::getCamPosition()
{
	return camPosition;
}

Point CameraMain::getsCamPosition(){
	return Point(XMVectorGetX(camPosition), XMVectorGetY(camPosition), XMVectorGetZ(camPosition));
}


void CameraMain::setCamPosition(float a, float b, float c, float d)
{
	//camPosition = XMVectorSet( 0.0f, 0.0f, -0.5f, 0.0f );
	camPosition = XMVectorSet(a, b, c, d);
}

XMVECTOR CameraMain::getCamTarget()
{
	return camTarget;
}

Point CameraMain::getsCamTarget(){
	return Point(XMVectorGetX(camTarget), XMVectorGetY(camTarget), XMVectorGetZ(camTarget));
}

void CameraMain::setCamTarget(float a, float b, float c, float d)
{
	//camTarget = XMVectorSet( 0.0f, 0.0f, 0.0f, 0.0f );
	camTarget = XMVectorSet(a, b, c, d);
}

XMVECTOR CameraMain::getCamUp()
{
	return camUp;
}

void CameraMain::setCamUp(float a, float b, float c, float d)
{
	//camUp = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	camUp = XMVectorSet(a, b, c, d);
}

Point CameraMain::getsCamUp(){
	return Point(XMVectorGetX(camUp), XMVectorGetY(camUp), XMVectorGetZ(camUp));
}

///////////////**************new**************////////////////////
void CameraMain::setDefaultForward(float a, float b, float c, float d)
{
	//DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DefaultForward = XMVectorSet(a, b, c, d);
}

XMVECTOR CameraMain::getDefaultForward()
{
	return DefaultForward;
}

void CameraMain::setDefaultRight(float a, float b, float c, float d)
{
	//DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DefaultRight = XMVectorSet(a, b, c, d);
}

XMVECTOR CameraMain::getDefaultRight()
{
	return DefaultRight;
}

void CameraMain::setCamForward(float a, float b, float c, float d)
{
	//camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	camForward = XMVectorSet(a, b, c, d);
}

XMVECTOR CameraMain::getCamForward()
{
	return camForward;
}

void CameraMain::setCamRight(float a, float b, float c, float d)
{
	//camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	camRight = XMVectorSet(a, b, c, d);
}

XMVECTOR CameraMain::getCamRight()
{
	return camRight;
}

void CameraMain::setMoveLeftRight(float a)
{
	moveLeftRight = a;
}

float CameraMain::getMoveLeftRight()
{
	return moveLeftRight;
}

void CameraMain::setMoveBackForward(float a)
{
	moveBackForward = a;
}

float CameraMain::getMoveBackForward()
{
	return moveBackForward;
}

void CameraMain::setCamYaw(float a)
{
	camYaw = a;
}

float CameraMain::getCamYaw()
{
	return camYaw;
}

void CameraMain::setCamPitch(float a)
{
	camPitch = a;
}

float CameraMain::getCamPitch()
{
	return camPitch;
}

void CameraMain::UpdateCamera()
{
	camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camTarget = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	camTarget = XMVector3Normalize(camTarget);

	XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(camYaw);

	camRight = XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
	camUp = XMVector3TransformCoord(camUp, RotateYTempMatrix);
	camForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);

	camPosition += moveLeftRight*camRight;
	camPosition += moveBackForward*camForward;

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	camTarget = camPosition + camTarget;

	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
}



