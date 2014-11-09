#ifndef CUBEMAP_H
#define CUBEMAP_H

#include "GeometryGenerator.h"
#include "Camera.h"
#include "Vertex.h"
#include <math.h>
#include "Effects.h"

class Camera;

class Cubemap{
public:
	Cubemap(ID3D11Device* device, const std::wstring& cubemapFilename, float SphereRadius);
	~Cubemap();

	// Cubemap's ShaderResourceViews
	ID3D11ShaderResourceView* CubeMapSRV();										

	void Draw(ID3D11DeviceContext* dc, const Camera& camera);

private:
	Cubemap(const Cubemap& rhs);
	Cubemap& operator=(const Cubemap& rhs);

private:
	// vertex buffer
	ID3D11Buffer* mVB;
	// index buffer
	ID3D11Buffer* mIB;
	// Cubemap's ShaderResourceViews
	ID3D11ShaderResourceView* mCubeMapSRV;

	UINT mIndexCount;
};

#endif // CUBEMAP_H