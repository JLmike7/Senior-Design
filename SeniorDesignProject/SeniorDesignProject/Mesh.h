#ifndef MESH_H
#define MESH_H

#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>

#include "Struct.h"
#include "VertexMain.h"

class Mesh{
public:
	Mesh();
	~Mesh();

	//Mesh variables. Each loaded mesh will need its own set of these
	bool md5;	//used to determine if this mesh is an MD5 model or a static OBJ model, OBJ as default
	ID3D11Buffer* vertBuff;
	ID3D11Buffer* indexBuff;
	std::vector<XMFLOAT3> vertPosArray;
	std::vector<DWORD> vertIndexArray;
	XMMATRIX meshWorld;
	Struct::Model3D MD5Model;
	int subsetCount = 0;
	std::vector<int> subsetIndexStart;
	std::vector<int> subsetTexture;

	//Textures and material variables, used for all mesh's loaded
	std::vector<ID3D11ShaderResourceView*> meshSRV;
	std::vector<std::wstring> textureNameArray;

	std::wstring filename;		//.obj filename

	//Define LoadObjModel function after we create surfaceMaterial structure
	bool LoadObjModel(
		std::wstring objFilename,
		std::vector<Struct::SurfaceMaterial>& material,		//vector of material structures
		bool isRHCoordSys,							//true if model was created in right hand coord system
		bool computeNormals,						//true to compute the normals, false to use the files normals
		ID3D11Device* device,
		IDXGISwapChain* SwapChain);

	//LoadMD5Model() function prototype
	bool LoadMD5Model(std::wstring filename, ID3D11Device* device, IDXGISwapChain* SwapChain);

	bool LoadMD5Anim(std::wstring filename, IDXGISwapChain* SwapChain);

	void UpdateMD5Model(float deltaTime, int animation, ID3D11DeviceContext* d3d11DevCon);

private:
};

#endif // MESH_H