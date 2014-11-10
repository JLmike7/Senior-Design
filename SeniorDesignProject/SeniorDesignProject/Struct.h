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

		///////////////**************new**************////////////////////
		//These will be used for the pixel shader
		XMFLOAT4 difColor;
		bool hasTexture;
		///////////////**************new**************////////////////////
	};

	///////////////**************new**************////////////////////
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
	///////////////**************new**************////////////////////

	struct cbPerFrame
	{
		Light  light;
	};

	///////////////**************new**************////////////////////
	//Create material structure
	struct SurfaceMaterial
	{
		std::wstring matName;
		XMFLOAT4 difColor;
		int texArrayIndex;
		bool hasTexture;
		bool transparent;
	};
	///////////////**************new**************////////////////////
}

/*class InputLayoutDesc
{
public:
	static const D3D11_INPUT_ELEMENT_DESC layout[3];
};*/


#endif // STRUCT_H
