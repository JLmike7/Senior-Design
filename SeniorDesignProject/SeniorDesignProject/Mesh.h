#ifndef MESH_H
#define MESH_H

//#include "d3dUtil.h"
//#include "Vertex.h"
#include <d3d11.h>
#include <xnamath.h>
//#include <string>
//#include <vector>
///////////////**************new**************////////////////////
#include <vector>
#include <fstream>
#include <istream>
///////////////**************new**************////////////////////

#include <sstream>

#include <d3dx11.h>

#include "Struct.h"
#include "VertexMain.h"

//class Camera;

class Mesh{
public:
	//ID3D11Buffer* sphereVertBuffer;
	//ID3D11Buffer* sphereIndexBuffer;

	//Mesh(ID3D11Device* device);
	Mesh();			//.obj filename);
	~Mesh();

	//void CreateSphere(int LatLines, int LongLines, ID3D11Device* d3d11Device);
	///////////////**************new**************////////////////////
	//Mesh variables. Each loaded mesh will need its own set of these
	ID3D11Buffer* vertBuff;
	ID3D11Buffer* indexBuff;
	XMMATRIX meshWorld;
	int subsetCount = 0;
	std::vector<int> subsetIndexStart;
	std::vector<int> subsetTexture;

	//Textures and material variables, used for all mesh's loaded
	std::vector<ID3D11ShaderResourceView*> meshSRV;
	std::vector<std::wstring> textureNameArray;
	///////////////**************new**************////////////////////

	std::wstring filename;		//.obj filename

	///////////////**************new**************////////////////////
	//Define LoadObjModel function after we create surfaceMaterial structure
	bool LoadObjModel(
		std::wstring objFilename,
		std::vector<Struct::SurfaceMaterial>& material,		//vector of material structures
		bool isRHCoordSys,							//true if model was created in right hand coord system
		bool computeNormals,						//true to compute the normals, false to use the files normals
		ID3D11Device* device,
		IDXGISwapChain* SwapChain);
	///////////////**************new**************////////////////////


private:
	//int NumSphereVertices;
	//int NumSphereFaces;
};

#endif // MESH_H