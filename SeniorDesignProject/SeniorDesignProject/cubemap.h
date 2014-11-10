#ifndef CUBEMAP_H
#define CUBEMAP_H

//#include "d3dUtil.h"
#include "VertexMain.h"
#include <d3d11.h>
#include <string>
#include <vector>

class Camera;

class Cubemap{
public:
	ID3D11Buffer* sphereVertBuffer;
	ID3D11Buffer* sphereIndexBuffer;
	ID3D11VertexShader* SKYMAP_VS;
	ID3D11PixelShader* SKYMAP_PS;
	ID3D10Blob* SKYMAP_VS_Buffer;
	ID3D10Blob* SKYMAP_PS_Buffer;

	ID3D11ShaderResourceView* smrv;

	Cubemap(ID3D11Device* device);
	~Cubemap();

	void CreateSphere(int LatLines, int LongLines, ID3D11Device* d3d11Device);

	void setNumSphereVertices(int a);
	int getNumSphereVertices();

	void setNumSphereFaces(int a);
	int getNumSphereFaces();

private:

	int NumSphereVertices;
	int NumSphereFaces;
};

#endif // CUBEMAP_H