#ifndef _FRUSTUMCLASS_H_
#define _FRUSTUMCLASS_H_

#include <d3d11.h>
#include <xnamath.h> 

class FrustumClass
{
public:
	FrustumClass();
	FrustumClass(const FrustumClass&);
	~FrustumClass();

	void ConstructFrustum(float, CXMMATRIX, CXMMATRIX );

	bool CheckPoint(float, float, float);
	bool CheckCube(float, float, float, float);
	bool CheckSphere(float, float, float, float);
	bool CheckRectangle(float, float, float, float, float, float);

private:
	XMVECTOR m_planes[6];
};

#endif