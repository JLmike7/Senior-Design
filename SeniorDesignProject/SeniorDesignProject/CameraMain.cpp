//***************************************************************************************
// CameraMain.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "CameraMain.h"

CameraMain::CameraMain()
{
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

void CameraMain::setCamProjection(float x, float y, float z, float w)
{
	camProjection = XMMatrixPerspectiveFovLH(x, y, z, w);
}


XMVECTOR CameraMain::getCamPosition()
{
	return camPosition;
}

void CameraMain::setCamPosition(float x, float y, float z, float w)
{
	camPosition = XMVectorSet(x, y, z, w);
}

XMVECTOR CameraMain::getCamTarget()
{
	return camTarget;
}

void CameraMain::setCamTarget(float x, float y, float z, float w)
{
	camTarget = XMVectorSet(x, y, z, w);
}

XMVECTOR CameraMain::getCamUp()
{
	return camUp;
}

void CameraMain::setCamUp(float x, float y, float z, float w)
{
	camUp = XMVectorSet(x, y, z, w);
}

void CameraMain::setDefaultForward(float x, float y, float z, float w)
{
	DefaultForward = XMVectorSet(x, y, z, w);
}

XMVECTOR CameraMain::getDefaultForward()
{
	return DefaultForward;
}

void CameraMain::setDefaultRight(float x, float y, float z, float w)
{
	DefaultRight = XMVectorSet(x, y, z, w);
}

XMVECTOR CameraMain::getDefaultRight()
{
	return DefaultRight;
}

void CameraMain::setCamForward(float x, float y, float z, float w)
{
	camForward = XMVectorSet(x, y, z, w);
}

XMVECTOR CameraMain::getCamForward()
{
	return camForward;
}

void CameraMain::setCamRight(float x, float y, float z, float w)
{
	camRight = XMVectorSet(x, y, z, w);
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
