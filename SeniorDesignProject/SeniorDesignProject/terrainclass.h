////////////////////////////////////////////////////////////////////////////////
// Filename: terrainclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TERRAINCLASS_H_
#define _TERRAINCLASS_H_

const int TEXTURE_REPEAT = 8;

#include <d3d11.h>
#include <xnamath.h>
#include <stdio.h>

#include "textureclass.h"

class TerrainClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	    XMFLOAT3 normal;
	};

	struct HeightMapType 
	{ 
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float r, g, b;
	};

	struct VectorType 
	{ 
		float x, y, z;
	};

public:
	TerrainClass();
	TerrainClass(const TerrainClass&);
	~TerrainClass();

	bool Initialize(ID3D11Device* device, char* heightMapFilename, WCHAR* textureFilename, char* colorMapFilename);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

	int GetVertexCount();
	void CopyVertexArray(void*);

private:
	bool LoadHeightMap(char*);
	void NormalizeHeightMap();
	bool CalculateNormals();
	void ShutdownHeightMap();

	void CalculateTextureCoordinates();
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();

	bool LoadColorMap(char* filename);
	
private:
	int m_terrainWidth, m_terrainHeight;
	HeightMapType* m_heightMap;
	TextureClass* m_Texture;
	int m_vertexCount;
	VertexType* m_vertices;
};

#endif