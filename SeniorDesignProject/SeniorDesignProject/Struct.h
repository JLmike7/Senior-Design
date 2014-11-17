#ifndef STRUCT_H
#define STRUCT_H

//#include <windows.h>
//#include <d3d11.h>
//#include <d3dx11.h>
//#include <d3dx10.h>
#include <xnamath.h>
#include "VertexMain.h"

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
	};///////////////**************new**************////////////////////
	struct Joint
	{
		std::wstring name;
		int parentID;

		XMFLOAT3 pos;
		XMFLOAT4 orientation;
	};

	///////////////**************new**************////////////////////
	struct BoundingBox
	{
		XMFLOAT3 min;
		XMFLOAT3 max;
	};

	struct FrameData
	{
		int frameID;
		std::vector<float> frameData;
	};
	struct AnimJointInfo
	{
		std::wstring name;
		int parentID;

		int flags;
		int startIndex;
	};

	struct ModelAnimation
	{
		int numFrames;
		int numJoints;
		int frameRate;
		int numAnimatedComponents;

		float frameTime;
		float totalAnimTime;
		float currAnimTime;

		std::vector<AnimJointInfo> jointInfo;
		std::vector<BoundingBox> frameBounds;
		std::vector<Joint>	baseFrameJoints;
		std::vector<FrameData>	frameData;
		std::vector<std::vector<Joint>> frameSkeleton;
	};
	///////////////**************new**************////////////////////

	struct Weight
	{
		int jointID;
		float bias;
		XMFLOAT3 pos;
		///////////////**************new**************////////////////////
		XMFLOAT3 normal;
		///////////////**************new**************////////////////////
	};

	struct ModelSubset
	{
		int texArrayIndex;
		int numTriangles;

		std::vector<Vertex::Vertex> vertices;
		std::vector<XMFLOAT3> jointSpaceNormals;
		std::vector<DWORD> indices;
		std::vector<Weight> weights;

		std::vector<XMFLOAT3> positions;

		ID3D11Buffer* vertBuff;
		ID3D11Buffer* indexBuff;
	};

	struct Model3D
	{
		int numSubsets;
		int numJoints;

		std::vector<Joint> joints;
		std::vector<ModelSubset> subsets;

		///////////////**************new**************////////////////////
		std::vector<ModelAnimation> animations;
		///////////////**************new**************////////////////////
	};
	///////////////**************new**************////////////////////
}

#endif // STRUCT_H
