#ifndef STRUCT_H
#define STRUCT_H

//#include <windows.h>
//#include <d3d11.h>
//#include <d3dx11.h>
//#include <d3dx10.h>
#include <xnamath.h>

namespace Struct
{
	struct cbPerObject
	{
		XMMATRIX  WVP;
		XMMATRIX  World;

		//These will be used for the pixel shader
		XMFLOAT4 difColor;
		BOOL hasTexture;
		//Because of HLSL structure packing, we will use windows BOOL
		//instead of bool because HLSL packs things into 4 bytes, and
		//bool is only one byte, where BOOL is 4 bytes
		BOOL hasNormMap;
	};

	struct Light
	{
		Light()
		{
			ZeroMemory(this, sizeof(Light));
		}
		XMFLOAT3 pos;
		float range;
		XMFLOAT3 dir;
		float cone;
		XMFLOAT3 att;
		float pad2;
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
	};

	struct cbPerFrame
	{
		Light  light;
	};

	//Create material structure
	struct SurfaceMaterial
	{
		std::wstring matName;
		XMFLOAT4 difColor;
		int texArrayIndex;
		int normMapTexArrayIndex;
		bool hasNormMap;
		bool hasTexture;
		bool transparent;
	};
}

#endif // STRUCT_H
