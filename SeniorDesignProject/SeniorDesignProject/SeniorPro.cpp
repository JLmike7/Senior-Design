#include "d3dApp.h"
#include "CameraMain.h"
#include "VertexMain.h"
#include "Cubemap.h"
#include "Mesh.h"
#include "Collision.h"
#include "quadTreeClass.h"
#include "terrainclass.h"
#include "terrainshaderclass.h"
#include "textureclass.h"

#define MESHCOUNT 8
#define ENEMYCOUNT 10
#define ITEMCOUNT 30
#define AMMOCOUNT 30

class SeniorPro : public D3DApp
{
public:
	SeniorPro(HINSTANCE);
	~SeniorPro();

	bool InitScene();
	void UpdateScene(double time);
	void DrawScene();
	void RenderText(std::wstring text, int inInt);
	void DetectInput(double time);
	void drawModel(Mesh* mesh, bool transparent);
	void drawMD5Model(Mesh* mesh);

	void pickRayVector(float mouseX, float mouseY, XMVECTOR& pickRayInWorldSpacePos, XMVECTOR& pickRayInWorldSpaceDir);
	float pick(XMVECTOR pickRayInWorldSpacePos,
		XMVECTOR pickRayInWorldSpaceDir,
		std::vector<XMFLOAT3>& vertPosArray,
		std::vector<DWORD>& indexPosArray,
		XMMATRIX& worldSpace);
	bool PointInTriangle(XMVECTOR& triV1, XMVECTOR& triV2, XMVECTOR& triV3, XMVECTOR& point);

private:
	CameraMain mCam;

	Collision coll[ENEMYCOUNT];
	Collision itemColl[ITEMCOUNT];
	Collision ammoColl[AMMOCOUNT];
	Collision win;
	bool move;

	Cubemap* mCubemap;

	Mesh meshArray[MESHCOUNT];

	Struct::HeightMapInfo hmInfo;
	XMMATRIX groundWorld;
	XMMATRIX sphereWorld;

	XMMATRIX Rotation;
	XMMATRIX Scale;
	XMMATRIX Translation;
	float rot = 0.01f;

	UINT stride = sizeof(Vertex::Vertex);
	UINT offset = 0;

	Mesh enemyArray[ENEMYCOUNT];
	//Mesh enemyCollisionBox[ENEMYCOUNT];
	Mesh itemArray[ITEMCOUNT];
	Mesh ammoArray[AMMOCOUNT];
	int* enemyHit = new int[ENEMYCOUNT];

	bool enemyBox = false; //used to switch between bipeds and boxes

	TerrainClass* m_Terrain;
	TerrainShaderClass* m_TerrainShader;
	FrustumClass* m_Frustum;
	QuadTreeClass* m_QuadTree;
};
//run initializemainwindow

#pragma region Sound_Initialization
//Music
IXAudio2* g_engine;
IXAudio2SourceVoice* g_source;
IXAudio2MasteringVoice* g_master;

//Gunshot
IXAudio2* g_engineGun;
IXAudio2SourceVoice* g_sourceGun;
IXAudio2MasteringVoice* g_masterGun;

//Dead
IXAudio2* g_engineDead;
IXAudio2SourceVoice* g_sourceDead;
IXAudio2MasteringVoice* g_masterDead;

//Revive
IXAudio2* g_engineRevive;
IXAudio2SourceVoice* g_sourceRevive;
IXAudio2MasteringVoice* g_masterRevive;

//Reload
IXAudio2* g_engineReload;
IXAudio2SourceVoice* g_sourceReload;
IXAudio2MasteringVoice* g_masterReload;

//Hit
IXAudio2* g_engineHit;
IXAudio2SourceVoice* g_sourceHit;
IXAudio2MasteringVoice* g_masterHit;

//Blaster
IXAudio2* g_engineBlaster;
IXAudio2SourceVoice* g_sourceBlaster;
IXAudio2MasteringVoice* g_masterBlaster;

//Sound stuff
Wave buffer; //Music
Wave buffer2; //gunshot
Wave buffer3; //dead
Wave buffer4; //revive
Wave buffer5; //reload
Wave buffer6; //bullethit
Wave buffer7; //blaster

#pragma endregion Sound_Initialization

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	SeniorPro theApp(hInstance);
	srand(time(NULL));
	//must call this for COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//create the engine
	if (FAILED(XAudio2Create(&g_engine)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engine->CreateMasteringVoice(&g_master)))
	{
		g_engine->Release();
		CoUninitialize();
		return -2;
	}

	//helper class to load wave files; trust me, this makes it MUCH easier


	//load a wave file
	if (!buffer.load("Music2.wav"))
	{
		g_engine->Release();
		CoUninitialize();
		return -3;
	}

	//create the source voice, based on loaded wave format
	if (FAILED(g_engine->CreateSourceVoice(&g_source, buffer.wf())))
	{
		g_engine->Release();
		CoUninitialize();
		return -4;
	}

	//Gunshot

	//create the engine
	if (FAILED(XAudio2Create(&g_engineGun)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engineGun->CreateMasteringVoice(&g_masterGun)))
	{
		g_engineGun->Release();
		CoUninitialize();
		return -2;
	}

	//load a wave file
	if (!buffer2.load("Gunshot.wav"))
	{
		g_engineGun->Release();
		CoUninitialize();
	}

	//create the source voice, based on loaded wave format
	if (FAILED(g_engineGun->CreateSourceVoice(&g_sourceGun, buffer2.wf())))
	{
		g_engineGun->Release();
		CoUninitialize();
	}

	//Dead

	//create the engine
	if (FAILED(XAudio2Create(&g_engineDead)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engineDead->CreateMasteringVoice(&g_masterDead)))
	{
		g_engineDead->Release();
		CoUninitialize();
		return -2;
	}

	//load a wave file
	if (!buffer3.load("Fatality.wav"))
	{
		g_engineDead->Release();
		CoUninitialize();
	}

	//create the source voice, based on loaded wave format
	if (FAILED(g_engineDead->CreateSourceVoice(&g_sourceDead, buffer3.wf())))
	{
		g_engineDead->Release();
		CoUninitialize();
	}
	//blaster

	//create the engine
	if (FAILED(XAudio2Create(&g_engineBlaster)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engineBlaster->CreateMasteringVoice(&g_masterBlaster)))
	{
		g_engineBlaster->Release();
		CoUninitialize();
		return -2;
	}

	//load a wave file
	if (!buffer7.load("blaster.wav"))
	{
		g_engineBlaster->Release();
		CoUninitialize();
	}

	//create the source voice, based on loaded wave format
	if (FAILED(g_engineBlaster->CreateSourceVoice(&g_sourceBlaster, buffer7.wf())))
	{
		g_engineBlaster->Release();
		CoUninitialize();
	}

	//revive

	//create the engine
	if (FAILED(XAudio2Create(&g_engineRevive)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engineRevive->CreateMasteringVoice(&g_masterRevive)))
	{
		g_engineRevive->Release();
		CoUninitialize();
		return -2;
	}

	//load a wave file
	if (!buffer4.load("Revive.wav"))
	{
		g_engineRevive->Release();
		CoUninitialize();
	}

	//create the source voice, based on loaded wave format
	if (FAILED(g_engineRevive->CreateSourceVoice(&g_sourceRevive, buffer4.wf())))
	{
		g_engineRevive->Release();
		CoUninitialize();
	}

	//reload

	//create the engine
	if (FAILED(XAudio2Create(&g_engineReload)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engineReload->CreateMasteringVoice(&g_masterReload)))
	{
		g_engineReload->Release();
		CoUninitialize();
		return -2;
	}

	//load a wave file
	if (!buffer5.load("Reload.wav"))
	{
		g_engineGun->Release();
		CoUninitialize();
	}

	//create the source voice, based on loaded wave format
	if (FAILED(g_engineReload->CreateSourceVoice(&g_sourceReload, buffer5.wf())))
	{
		g_engineReload->Release();
		CoUninitialize();
	}

	//bullethit
	//create the engine
	if (FAILED(XAudio2Create(&g_engineHit)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engineHit->CreateMasteringVoice(&g_masterHit)))
	{
		g_engineHit->Release();
		CoUninitialize();
		return -2;
	}

	//load a wave file
	if (!buffer6.load("BulletHitFlesh.wav"))
	{
		g_engineHit->Release();
		CoUninitialize();
	}

	//create the source voice, based on loaded wave format
	if (FAILED(g_engineHit->CreateSourceVoice(&g_sourceHit, buffer6.wf())))
	{
		g_engineHit->Release();
		CoUninitialize();
	}
	if (!theApp.InitializeWindow())
	{
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}
	if (!theApp.InitializeDirect3d11App(hInstance))	//Initialize Direct3D
	{
		MessageBox(0, L"Direct3D Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	if (!theApp.InitScene())	//Initialize our scene
	{
		MessageBox(0, L"Scene Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	if (!theApp.InitDirectInput(hInstance))
	{
		MessageBox(0, L"Direct Input Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}


	return theApp.messageloop();
}

SeniorPro::SeniorPro(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
	//Camera information
	mCam.setCamPosition(60.0f, 10.0f, 60.0f, 0.0f);
	mCam.setCamTarget(0.0f, 0.0f, 0.0f, 0.0f);
	mCam.setCamUp(0.0f, 1.0f, 0.0f, 0.0f);

	//Set the View matrix
	mCam.setCamView(mCam.getCamPosition(), mCam.getCamTarget(), mCam.getCamUp());

	//Set the Projection matrix
	mCam.setCamProjection(0.4f*3.14f, Width / Height, 1.0f, 1000.0f);

	mCam.setDefaultForward(0.0f, 0.0f, 1.0f, 0.0f);
	mCam.setDefaultRight(1.0f, 0.0f, 0.0f, 0.0f);
	mCam.setCamForward(0.0f, 0.0f, 1.0f, 0.0f);
	mCam.setCamRight(1.0f, 0.0f, 0.0f, 0.0f);

	mCam.setMoveLeftRight(0.0f);
	mCam.setMoveBackForward(0.0f);

	mCam.setCamYaw(0.0f);
	mCam.setCamPitch(0.0f);

	for (int i = 0; i < 30; i++)
	{
		EMoveX[i] = 0.01f;
		EMoveZ[i] = 0.01f;
	}

	for (int i = 0; i < 30; i++)
	{
		ERot[i] = 0.01f;
	}

	m_Terrain = 0;
	m_TerrainShader = 0;
	m_Frustum = 0;
	m_QuadTree = 0;

};

SeniorPro::~SeniorPro()
{//again, for COM
	CoUninitialize();
	g_engine->Release();
	g_engineDead->Release();
	g_engineGun->Release();
	g_engineReload->Release();
	g_engineRevive->Release();
	g_engineHit->Release();

	// Release the quad tree object.
	if (m_QuadTree)
	{
		m_QuadTree->Shutdown();
		delete m_QuadTree;
		m_QuadTree = 0;
	}

	// Release the frustum object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the terrain shader object.
	if (m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the terrain object.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}
};

bool SeniorPro::InitScene()
{
	//Init hit person
	hitMe = 1;
	InitD2DScreenTexture();
	
	// Create cubemap
	mCubemap = new Cubemap(d3d11Device);

	if (!meshArray[0].LoadObjModel(L"HUD3.obj", material, true, true, d3d11Device, SwapChain))
		return false;
	if (!meshArray[1].LoadObjModel(L"ak47.obj", material, true, false, d3d11Device, SwapChain))
		return false;
	if (!meshArray[2].LoadObjModel(L"sa80.obj", material, true, false, d3d11Device, SwapChain))
		return false;
	if (!meshArray[3].LoadObjModel(L"spaceCompound.obj", material, true, false, d3d11Device, SwapChain))
		return false;
	if (!meshArray[4].LoadObjModel(L"win.obj", material, true, false, d3d11Device, SwapChain))
		return false;
	if (!meshArray[5].LoadObjModel(L"Moon.obj", material, true, true, d3d11Device, SwapChain))
		return false;
	if (!meshArray[6].LoadObjModel(L"Menu.obj", material, true, false, d3d11Device, SwapChain))
		return false;
	if (!meshArray[7].LoadObjModel(L"ToT.obj", material, true, true, d3d11Device, SwapChain))
		return false;
	/*//if (!meshArray[3].LoadObjModel(L"ToT.obj", material, true, true, d3d11Device, SwapChain))
		return false;
	if (!meshArray[4].LoadObjModel(L"DoorLeft.obj", material, true, true, d3d11Device, SwapChain))
		return false;
	if (!meshArray[5].LoadObjModel(L"DoorRight.obj", material, true, true, d3d11Device, SwapChain))
		return false;
	if (!meshArray[6].LoadObjModel(L"DoorLeft.obj", material, true, true, d3d11Device, SwapChain))
		return false;
	if (!meshArray[7].LoadObjModel(L"DoorRight.obj", material, true, true, d3d11Device, SwapChain))
		return false;*/
	//Enemy.obj, DoorLeft.obj, DoorRight.obj

	//Items
	for (int i = 0; i < ITEMCOUNT; i++)
	{
		if (!itemArray[i].LoadObjModel(L"eclipse.obj", material, true, false, d3d11Device, SwapChain))
			return false;
	}
	//Ammo
	for (int i = 0; i < ITEMCOUNT; i++)
		{
		if (!ammoArray[i].LoadObjModel(L"ammo.obj", material, true, false, d3d11Device, SwapChain))
			return false;
	}


	//Enemies
	for (int i = 0; i < ENEMYCOUNT; i++)
		{
		if (!enemyArray[i].LoadObjModel(L"Enemy.obj", material, true, false, d3d11Device, SwapChain))
			return false;

			if (!enemyArray[i].LoadMD5Model(L"boy.md5mesh", d3d11Device, SwapChain))
				return false;

			if (!enemyArray[i].LoadMD5Anim(L"boy.md5anim", SwapChain))
				return false;
		}

	//Compile Shaders from shader file
	hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "VS", "vs_4_0", 0, 0, 0, &VS_Buffer, 0, 0);
	hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "PS", "ps_4_0", 0, 0, 0, &PS_Buffer, 0, 0);
	hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "D2D_PS", "ps_4_0", 0, 0, 0, &D2D_PS_Buffer, 0, 0);
	hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "SKYMAP_VS", "vs_4_0", 0, 0, 0, &mCubemap->SKYMAP_VS_Buffer, 0, 0);
	hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "SKYMAP_PS", "ps_4_0", 0, 0, 0, &mCubemap->SKYMAP_PS_Buffer, 0, 0);

	//Create the Shader Objects
	hr = d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
	hr = d3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
	hr = d3d11Device->CreatePixelShader(D2D_PS_Buffer->GetBufferPointer(), D2D_PS_Buffer->GetBufferSize(), NULL, &D2D_PS);
	hr = d3d11Device->CreateVertexShader(mCubemap->SKYMAP_VS_Buffer->GetBufferPointer(), mCubemap->SKYMAP_VS_Buffer->GetBufferSize(), NULL, &mCubemap->SKYMAP_VS);
	hr = d3d11Device->CreatePixelShader(mCubemap->SKYMAP_PS_Buffer->GetBufferPointer(), mCubemap->SKYMAP_PS_Buffer->GetBufferSize(), NULL, &mCubemap->SKYMAP_PS);

	//Set Vertex and Pixel Shaders
	d3d11DevCon->VSSetShader(VS, 0, 0);
	d3d11DevCon->PSSetShader(PS, 0, 0);

	//Regular light settings
	light.dir = XMFLOAT3(0.0f, 1.0f, 0.0f);
	light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	//Spotlight Light settings
	/*light.pos = XMFLOAT3(0.0f, 1.0f, 0.0f);
	light.dir = XMFLOAT3(0.0f, 0.0f, 1.0f);
	light.range = 1000.0f;
	light.cone = 20.0f;
	light.att = XMFLOAT3(0.4f, 0.02f, 0.000f);
	light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);*/

	/*//Create the vertex buffer
	Vertex::Vertex v[] =
	{
		// Bottom Face
		Vertex::Vertex(-1.0f, -1.0f, -1.0f, 100.0f, 100.0f, 0.0f, 1.0f, 0.0f),
		Vertex::Vertex(1.0f, -1.0f, -1.0f, 0.0f, 100.0f, 0.0f, 1.0f, 0.0f),
		Vertex::Vertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		Vertex::Vertex(-1.0f, -1.0f, 1.0f, 100.0f, 0.0f, 0.0f, 1.0f, 0.0f),
	};

	DWORD indices[] = {
		0, 1, 2,
		0, 2, 3,
	};*/

	#pragma region Terrain
	HeightMapLoad("heightmap.bmp", hmInfo);		// Load the heightmap and store it into hmInfo

	int cols = hmInfo.terrainWidth;
	int rows = hmInfo.terrainHeight;

	//Create the grid
	NumVertices = rows * cols;
	NumFaces = (rows - 1)*(cols - 1) * 2;

	std::vector<Vertex::Vertex> v(NumVertices);

	for (DWORD i = 0; i < rows; ++i)
	{
		for (DWORD j = 0; j < cols; ++j)
		{
			v[i*cols + j].pos = hmInfo.heightMap[i*cols + j];
			v[i*cols + j].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		}
	}

	std::vector<DWORD> indices(NumFaces * 3);

	int k = 0;
	int texUIndex = 0;
	int texVIndex = 0;
	for (DWORD i = 0; i < rows - 1; i++)
	{
		for (DWORD j = 0; j < cols - 1; j++)
		{
			indices[k] = i*cols + j;		// Bottom left of quad
			v[i*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 1.0f);

			indices[k + 1] = i*cols + j + 1;		// Bottom right of quad
			v[i*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 1.0f);

			indices[k + 2] = (i + 1)*cols + j;	// Top left of quad
			v[(i + 1)*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 0.0f);


			indices[k + 3] = (i + 1)*cols + j;	// Top left of quad
			v[(i + 1)*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 0.0f);

			indices[k + 4] = i*cols + j + 1;		// Bottom right of quad
			v[i*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 1.0f);

			indices[k + 5] = (i + 1)*cols + j + 1;	// Top right of quad
			v[(i + 1)*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 0.0f);

			k += 6; // next quad

			texUIndex++;
		}
		texUIndex = 0;
		texVIndex++;
	}

	//////////////////////Compute Normals///////////////////////////
	//Now we will compute the normals for each vertex using normal averaging
	std::vector<XMFLOAT3> tempNormal;

	//normalized and unnormalized normals
	XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

	//Used to get vectors (sides) from the position of the verts
	float vecX, vecY, vecZ;

	//Two edges of our triangle
	XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	//Compute face normals
	for (int i = 0; i < NumFaces; ++i)
	{
		//Get the vector describing one edge of our triangle (edge 0,2)
		vecX = v[indices[(i * 3)]].pos.x - v[indices[(i * 3) + 2]].pos.x;
		vecY = v[indices[(i * 3)]].pos.y - v[indices[(i * 3) + 2]].pos.y;
		vecZ = v[indices[(i * 3)]].pos.z - v[indices[(i * 3) + 2]].pos.z;
		edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);	//Create our first edge

		//Get the vector describing another edge of our triangle (edge 2,1)
		vecX = v[indices[(i * 3) + 2]].pos.x - v[indices[(i * 3) + 1]].pos.x;
		vecY = v[indices[(i * 3) + 2]].pos.y - v[indices[(i * 3) + 1]].pos.y;
		vecZ = v[indices[(i * 3) + 2]].pos.z - v[indices[(i * 3) + 1]].pos.z;
		edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);	//Create our second edge

		//Cross multiply the two edge vectors to get the un-normalized face normal
		XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));
		tempNormal.push_back(unnormalized);			//Save unormalized normal (for normal averaging)
	}

	//Compute vertex normals (normal Averaging)
	XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	int facesUsing = 0;
	float tX;
	float tY;
	float tZ;

	//Go through each vertex
	for (int i = 0; i < NumVertices; ++i)
	{
		//Check which triangles use this vertex
		for (int j = 0; j < NumFaces; ++j)
		{
			if (indices[j * 3] == i ||
				indices[(j * 3) + 1] == i ||
				indices[(j * 3) + 2] == i)
			{
				tX = XMVectorGetX(normalSum) + tempNormal[j].x;
				tY = XMVectorGetY(normalSum) + tempNormal[j].y;
				tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;

				normalSum = XMVectorSet(tX, tY, tZ, 0.0f);	//If a face is using the vertex, add the unormalized face normal to the normalSum
				facesUsing++;
			}
		}

		//Get the actual normal by dividing the normalSum by the number of faces sharing the vertex
		normalSum = normalSum / facesUsing;

		//Normalize the normalSum vector
		normalSum = XMVector3Normalize(normalSum);

		//Store the normal in our current vertex
		v[i].normal.x = XMVectorGetX(normalSum);
		v[i].normal.y = XMVectorGetY(normalSum);
		v[i].normal.z = XMVectorGetZ(normalSum);

		//Clear normalSum and facesUsing for next vertex
		normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		facesUsing = 0;
	}
	#pragma endregion Terrain

	bool result;
	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(d3d11Device, "heightmap.bmp", L"dirt01.dds", "colorm01.bmp");
	if (!result){
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if (!m_TerrainShader){
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(d3d11Device, hwnd);
	if (!result){
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the frustum object.
	m_Frustum = new FrustumClass;
	if (!m_Frustum)
	{
		return false;
	}

	// Create the quad tree object.
	m_QuadTree = new QuadTreeClass;
	if (!m_QuadTree){
		return false;
	}

	// Initialize the quad tree object.
	result = m_QuadTree->Initialize(m_Terrain, d3d11Device);
	if (!result){
		MessageBox(hwnd, L"Could not initialize the quad tree object.", L"Error", MB_OK);
		return false;
	}

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	/************************************New Stuff****************************************************/
	//indexBufferDesc.ByteWidth = sizeof(DWORD) * 2 * 3;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * NumFaces * 3;
	/************************************************************************************************/
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	/************************************New Stuff***************************************************/
	//iinitData.pSysMem = indices;
	iinitData.pSysMem = &indices[0];
	/************************************************************************************************/
	d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &squareIndexBuffer);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	/************************************New Stuff***************************************************/
	//vertexBufferDesc.ByteWidth = sizeof(Vertex::Vertex) * 4;
	vertexBufferDesc.ByteWidth = sizeof(Vertex::Vertex) * NumVertices;
	/************************************************************************************************/
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	/************************************New Stuff***************************************************/
	//vertexBufferData.pSysMem = v;
	vertexBufferData.pSysMem = &v[0];
	/************************************************************************************************/
	hr = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &squareVertBuffer);

	//Create the Input Layout
	hr = d3d11Device->CreateInputLayout(InputLayoutDesc::layout, numElements, VS_Buffer->GetBufferPointer(),
		VS_Buffer->GetBufferSize(), &vertLayout);

	//Set the Input Layout
	d3d11DevCon->IASetInputLayout(vertLayout);

	//Set Primitive Topology
	d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Create the Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = Width;
	viewport.Height = Height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//Set the Viewport
	d3d11DevCon->RSSetViewports(1, &viewport);

	//Create the buffer to send to the cbuffer in effect file
	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObj);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	hr = d3d11Device->CreateBuffer(&cbbd, NULL, &cbPerObjectBuffer);

	//Create the buffer to send to the cbuffer per frame in effect file
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(constbuffPerFrame);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	hr = d3d11Device->CreateBuffer(&cbbd, NULL, &cbPerFrameBuffer);

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
	rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbd;

	d3d11Device->CreateBlendState(&blendDesc, &d2dTransparency);

	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.DestBlend = D3D11_BLEND_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.DestBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbd;

	d3d11Device->CreateBlendState(&blendDesc, &Transparency);

	hr = D3DX11CreateShaderResourceViewFromFile(d3d11Device, L"Textures/grass.jpg",
		NULL, NULL, &CubesTexture, NULL);

	///Load Skymap's cube texture///
	D3DX11_IMAGE_LOAD_INFO loadSMInfo;
	loadSMInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	ID3D11Texture2D* SMTexture = 0;
	hr = D3DX11CreateTextureFromFile(d3d11Device, L"Textures/skymap.dds",
		&loadSMInfo, 0, (ID3D11Resource**)&SMTexture, 0);

	D3D11_TEXTURE2D_DESC SMTextureDesc;
	SMTexture->GetDesc(&SMTextureDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = SMTextureDesc.Format;
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = d3d11Device->CreateShaderResourceView(SMTexture, &SMViewDesc, &mCubemap->smrv);

	// Describe the Sample State
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//Create the Sample State
	hr = d3d11Device->CreateSamplerState(&sampDesc, &CubesTexSamplerState);

	D3D11_RASTERIZER_DESC cmdesc;

	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_BACK;
	cmdesc.FrontCounterClockwise = true;
	hr = d3d11Device->CreateRasterizerState(&cmdesc, &CCWcullMode);

	cmdesc.FrontCounterClockwise = false;

	hr = d3d11Device->CreateRasterizerState(&cmdesc, &CWcullMode);

	cmdesc.CullMode = D3D11_CULL_NONE;
	//cmdesc.FillMode = D3D11_FILL_WIREFRAME;
	hr = d3d11Device->CreateRasterizerState(&cmdesc, &RSCullNone);

	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	d3d11Device->CreateDepthStencilState(&dssDesc, &DSLessEqual);

	for (int i = 0; i < ENEMYCOUNT; i++)
	{
		/*exadd[i] = 0.0f;
		ezadd[i] = 0.0f;*/
		// collision for the heightmap
		float height;
		bool foundHeight;

		// Get the height of the triangle that is directly underneath the given camera position.
		foundHeight = m_QuadTree->GetHeightAtPosition(enemyXPos[i], enemyZPos[i], height);
		if (foundHeight)
		{
			// If there was a triangle under the camera then position the camera just above it by two units.
			enemyYPos[i] = height + 4.0f;
		}

		enemyXPos[i] = -20;
		enemyZPos[i] = 30;
		enemyRot[i] = 0;
		float startX = -30.0f;
		float startZ = 60.0f;
		// Init enemy locations
		for (int y = 0; y < ENEMYCOUNT; y++)
		{
			enemyXPos[y] = enemyXPos[y - 1] + 10.0f;
			enemyZPos[y] += 0.0f;
		}
		
		enemyHit[i] = 0.0f;

		//set the loaded enemy's world space
		//enemyArray[i].meshWorld = XMMatrixIdentity();

		exadd[i]++;

		if (exadd[i] == 10.0f){
			ezadd[i] -= 1.0f;
			exadd[i] = 0.0f;
		}

		Rotation = XMMatrixRotationY(enemyRot[i]);
		Scale = XMMatrixScaling(0.15f, 0.15f, 0.15f);
		Translation = XMMatrixTranslation(enemyXPos[i], enemyYPos[i], enemyZPos[i]);
		coll[i].setLocation(Point(enemyXPos[i], 2.0f, enemyZPos[i]));
		coll[i].setheight(3.0f);
		coll[i].setlength(3.0f);
		coll[i].setwidth(3.0f);
		//enemyArray[i].meshWorld = Rotation * Scale * Translation;
	}

	//Draw Initial items
	for (int i = 0; i < ITEMCOUNT; i++)
	{
		randItemX = rand() % 128;
		randItemZ = rand() % 128;

		itemX[i] = randItemX;
		itemZ[i] = randItemZ;

		float height;
		bool foundHeight;

		// Get the height of the triangle that is directly underneath the given camera position.
		foundHeight = m_QuadTree->GetHeightAtPosition(enemyXPos[i], enemyZPos[i], height);
		if (foundHeight)
		{
			// If there was a triangle under the camera then position the camera just above it by two units.
			itemY[i] = height + 2.0f;
		}

		//itemArray[i].meshWorld = XMMatrixIdentity();

		Rotation = XMMatrixRotationY(ItemRot);
		Scale = XMMatrixScaling(0.05f, 0.05f, 0.05f);
		Translation = XMMatrixTranslation(itemX[i], itemY[i], itemZ[i]);
		itemColl[i].setLocation(Point(itemX[i], itemY[i], itemZ[i]));
		itemColl[i].setheight(3.0f);
		itemColl[i].setlength(3.0f);
		itemColl[i].setwidth(3.0f);
		//itemArray[i].meshWorld = Rotation * Scale * Translation;
	}

	//Draw Initial items
	for (int i = 0; i < AMMOCOUNT; i++)
	{
		randAmmoX = rand() % 128;
		randAmmoZ = rand() % 128;

		ammoX[i] = randAmmoX;
		ammoZ[i] = randAmmoZ;

		float height;
		bool foundHeight;

		// Get the height of the triangle that is directly underneath the given camera position.
		foundHeight = m_QuadTree->GetHeightAtPosition(enemyXPos[i], enemyZPos[i], height);
		if (foundHeight)
		{
			// If there was a triangle under the camera then position the camera just above it by two units.
			ammoY[i] = height + 2.0f;
		}

		//ammoArray[i].meshWorld = XMMatrixIdentity();

		Rotation = XMMatrixRotationY(ammoRot);
		Scale = XMMatrixScaling(0.05f, 0.05f, 0.05f);
		Translation = XMMatrixTranslation(ammoX[i], ammoY[i], ammoZ[i]);
		ammoColl[i].setLocation(Point(ammoX[i], ammoY[i], ammoZ[i]));
		ammoColl[i].setheight(3.0f);
		ammoColl[i].setlength(3.0f);
		ammoColl[i].setwidth(3.0f);
		//ammoArray[i].meshWorld = Rotation * Scale * Translation;
	}
	//Initial win item location 
	winX = rand() % 128;
	winZ = rand() % 128;
	win.setLocation(Point((winX), 2.0f, (winZ)));
	win.setheight(3.0f);
	win.setlength(3.0f);
	win.setwidth(3.0f);
	return true;
}

void SeniorPro::UpdateScene(double time)
{
	float tempDist = 0.0f;
	float tempDist2 = 0.0f;
	float tempDist3 = 0.0f;
	float tempDist4 = 0.0f;
	float tempDist5 = 0.0f;
	float tempDist6 = 0.0f;
	float tempDist7 = 0.0f;
	float tempDist8 = 0.0f;
	float tempDist9 = 0.0f;
	float tempDist10 = 0.0f;

	// collision for the heightmap
	float height;
	bool foundHeight;

		//Reset cube1World
		groundWorld = XMMatrixIdentity();

		/************************************New Stuff****************************************************/
		/*//Define cube1's world space matrix
		Scale = XMMatrixScaling(500.0f, 10.0f, 500.0f);
		Translation = XMMatrixTranslation(0.0f, 10.0f, 0.0f);*/

		//Define terrains's world space matrix
		Scale = XMMatrixScaling(1.0f, 0.75f, 1.0f);
		Translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);//-64.0f, -10.0f, -64.0f);
		/************************************New Stuff****************************************************/

		//Set cube1's world space using the transformations
		groundWorld = Scale * Translation;

		//Reset sphereWorld
		sphereWorld = XMMatrixIdentity();

		//Define sphereWorld's world space matrix
		Scale = XMMatrixScaling(5.0f, 5.0f, 5.0f);
		//Make sure the sphere is always centered around camera
		Translation = XMMatrixTranslation(XMVectorGetX(mCam.getCamPosition()), XMVectorGetY(mCam.getCamPosition()), XMVectorGetZ(mCam.getCamPosition()));

		//Set sphereWorld's world space using the transformations
		sphereWorld = Scale * Translation;

		if (graphicsCase == 1) {

				meshArray[6].meshWorld = XMMatrixIdentity();
				Rotation = XMMatrixRotationY(0.0f);
				Scale = XMMatrixScaling(0.1f, 0.1f, 0.1f);
			Translation = XMMatrixTranslation(60.0f, 20.0f, 68.0f);
				meshArray[6].meshWorld = Rotation * Scale * Translation;

		}
		if (graphicsCase == 2){



	if (moveDoors == true)
	{
		if (moveLeft < 7.8f && moveRight < 7.8f)
			moveLeft += 0.01, moveRight += 0.01f;
	}
	else
	{
		if (moveLeft >= 0.0f && moveRight >= 0.0f)
			moveLeft -= 0.01f, moveRight -= 0.01f;
	}

	float closestDist = FLT_MAX;
	int hitIndex;
	//Get picking 
	XMVECTOR prwsPos, prwsDir, prwsPos2, prwsDir2, prwsPos3, prwsDir3, prwsPos4, prwsDir4, prwsPos5, prwsDir5;
	pickRayVector(0, 0, prwsPos, prwsDir);
	pickRayVector((Width / 2 - 1), 0, prwsPos2, prwsDir2);
	pickRayVector(((Width / -2) + 1), 0, prwsPos3, prwsDir3);
	pickRayVector(0, (Height / 2 - 1), prwsPos4, prwsDir4);
	pickRayVector(0, ((Height / -2) + 1), prwsPos5, prwsDir5);
	for (int i = 0; i < ENEMYCOUNT; i++)
	{
		if (enemyHit[i] == 0) //No need to check enemies already hit
		{
			//Set temp pick distances for camera vs objects
			tempDist = pick(prwsPos, prwsDir, enemyArray[i].vertPosArray, enemyArray[i].vertIndexArray, enemyArray[i].meshWorld);
			tempDist2 = pick(prwsPos2, prwsDir2, enemyArray[i].vertPosArray, enemyArray[i].vertIndexArray, enemyArray[i].meshWorld);
			tempDist3 = pick(prwsPos3, prwsDir3, enemyArray[i].vertPosArray, enemyArray[i].vertIndexArray, enemyArray[i].meshWorld);
			tempDist4 = pick(prwsPos4, prwsDir4, enemyArray[i].vertPosArray, enemyArray[i].vertIndexArray, enemyArray[i].meshWorld);
			tempDist5 = pick(prwsPos5, prwsDir5, enemyArray[i].vertPosArray, enemyArray[i].vertIndexArray, enemyArray[i].meshWorld);
		}
	}

	//Set temp pick distances for camera vs building
	tempDist6 = pick(prwsPos, prwsDir, meshArray[3].vertPosArray, meshArray[3].vertIndexArray, meshArray[3].meshWorld);
	tempDist7 = pick(prwsPos2, prwsDir2, meshArray[3].vertPosArray, meshArray[3].vertIndexArray, meshArray[3].meshWorld);
	tempDist8 = pick(prwsPos3, prwsDir3, meshArray[3].vertPosArray, meshArray[3].vertIndexArray, meshArray[3].meshWorld);
	tempDist9 = pick(prwsPos4, prwsDir4, meshArray[3].vertPosArray, meshArray[3].vertIndexArray, meshArray[3].meshWorld);
	tempDist10 = pick(prwsPos5, prwsDir5, meshArray[3].vertPosArray, meshArray[3].vertIndexArray, meshArray[3].meshWorld);

	//Set the pick distances for each object
	pickedDist = tempDist;
	pickedDist2 = tempDist2;
	pickedDist3 = tempDist3;
	pickedDist4 = tempDist4;
	pickedDist5 = tempDist5;
	pickedDist6 = tempDist6;
	pickedDist7 = tempDist7;
	pickedDist8 = tempDist8;
	pickedDist9 = tempDist9;
	pickedDist10 = tempDist10;
	for (int i = 0; i < MESHCOUNT; i++)
	{

#pragma region EnemyAI
		for (int i = 0; i < ENEMYCOUNT; i++)
		{
			randX = rand() % 1000;
			randZ = rand() % 1000;
			randRot = rand() % 1000;
			randAttack = rand() % 1000;



			// Get the height of the triangle that is directly underneath the given camera position.
			foundHeight = m_QuadTree->GetHeightAtPosition(enemyXPos[i], enemyZPos[i], height);
			if (foundHeight)
			{
				// If there was a triangle under the camera then position the camera just above it by two units.
				enemyYPos[i] = height + 2.0f;
			}

			//set the loaded enemy's world space
			enemyArray[i].meshWorld = XMMatrixIdentity();
			//Rotation = XMMatrixRotationY(3.14f);
				Scale = XMMatrixScaling(0.04f, 0.04f, 0.04f);
			
			//If distance is greater then 20, then randomly move
			if ((enemyXPos[i] - XMVectorGetX(mCam.getCamPosition()) <= 15 && enemyZPos[i] - XMVectorGetZ(mCam.getCamPosition()) <= 15)
				&& (enemyXPos[i] - XMVectorGetX(mCam.getCamPosition()) >= -15 && enemyZPos[i] - XMVectorGetZ(mCam.getCamPosition()) >= -15))
				//Player is near! Attack!
			{
				//If playerX > enemyX, increase enemyX, PlayerZ > enemyZ, increase enemyZ
				if (XMVectorGetX(mCam.getCamPosition()) >= enemyXPos[i] && XMVectorGetZ(mCam.getCamPosition()) >= enemyZPos[i])
				{
					//Rotate enemy toward player
					if ((mCam.getCamYaw() >= enemyRot[i]))
					{
						Rotation = XMMatrixRotationY(enemyRot[i] += 0.01f);
						if (enemyRot[i] > 6.28f)
							enemyRot[i] = 0.0f;
						if (enemyRot[i] < 0.0f)
							enemyRot[i] = 6.28f;
					}
					else
					{
						Rotation = XMMatrixRotationY(enemyRot[i] -= 0.01f);
						if (enemyRot[i] > 6.28f)
							enemyRot[i] = 0.0f;
						if (enemyRot[i] < 0.0f)
							enemyRot[i] = 6.28f;
					}

					//If enemy is close to player, stop!
					if ((enemyXPos[i] - XMVectorGetX(mCam.getCamPosition()) <= 5 && enemyZPos[i] - XMVectorGetZ(mCam.getCamPosition()) <= 5)
						&& (enemyXPos[i] - XMVectorGetX(mCam.getCamPosition()) >= -5 && enemyZPos[i] - XMVectorGetZ(mCam.getCamPosition()) >= -5))
					{
						//Attack on random
						if (randAttack % 33 == 0)
						{
							Player1.setHealth(Player1.getHealth() - 3);

							//start consuming audio in the source voice
							g_sourceBlaster->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceBlaster->Stop();
							g_sourceBlaster->FlushSourceBuffers();
							g_sourceBlaster->Start();

							//play the sound
							g_sourceBlaster->SubmitSourceBuffer(buffer7.xaBuffer());
							//}

							//start consuming audio in the source voice
							g_sourceHit->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceHit->Stop();
							g_sourceHit->FlushSourceBuffers();
							g_sourceHit->Start();

							//play the sound
							g_sourceHit->SubmitSourceBuffer(buffer6.xaBuffer());
							//}
						}

						Translation = XMMatrixTranslation(enemyXPos[i] += .00, enemyYPos[i], enemyZPos[i] += .00);
						coll[i].setLocation(Point(enemyXPos[i] += .00, enemyYPos[i], enemyZPos[i] += .00));
						
					}
					else
					{
						//Attack on random
						if (randAttack % 77 == 0)
						{
							Player1.setHealth(Player1.getHealth() - 3);

							//start consuming audio in the source voice
							g_sourceBlaster->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceBlaster->Stop();
							g_sourceBlaster->FlushSourceBuffers();
							g_sourceBlaster->Start();

							//play the sound
							g_sourceBlaster->SubmitSourceBuffer(buffer7.xaBuffer());
							//}

							//start consuming audio in the source voice
							g_sourceHit->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceHit->Stop();
							g_sourceHit->FlushSourceBuffers();
							g_sourceHit->Start();

							//play the sound
							g_sourceHit->SubmitSourceBuffer(buffer6.xaBuffer());
							//}
						}
						Translation = XMMatrixTranslation(enemyXPos[i] += .01f, enemyYPos[i], enemyZPos[i] += .01f);
						coll[i].setLocation(Point(enemyXPos[i] += .01f, enemyYPos[i], enemyZPos[i] += .01f));
					}
				}
				//If playerX > enemyX, increase enemyX, PlayerZ < enemyZ, decrease enemyZ
				if (XMVectorGetX(mCam.getCamPosition()) >= enemyXPos[i] && XMVectorGetZ(mCam.getCamPosition()) < enemyZPos[i])
				{
					//Rotate enemy toward player
					if ((mCam.getCamYaw() >= enemyRot[i]))
					{
						Rotation = XMMatrixRotationY(enemyRot[i] += 0.01f);
						if (enemyRot[i] > 6.28f)
							enemyRot[i] = 0.0f;
						if (enemyRot[i] < 0.0f)
							enemyRot[i] = 6.28f;
					}
					else
					{
						Rotation = XMMatrixRotationY(enemyRot[i] -= 0.01f);
						if (enemyRot[i] > 6.28f)
							enemyRot[i] = 0.0f;
						if (enemyRot[i] < 0.0f)
							enemyRot[i] = 6.28f;
					}
					//If enemy is close to player, stop!
					if ((enemyXPos[i] - XMVectorGetX(mCam.getCamPosition()) <= 5 && enemyZPos[i] - XMVectorGetZ(mCam.getCamPosition()) <= 5)
						&& (enemyXPos[i] - XMVectorGetX(mCam.getCamPosition()) >= -5 && enemyZPos[i] - XMVectorGetZ(mCam.getCamPosition()) >= -5))
					{
						//Attack on random
						if (randAttack % 33 == 0)
						{
							Player1.setHealth(Player1.getHealth() - 3);

							//start consuming audio in the source voice
							g_sourceBlaster->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceBlaster->Stop();
							g_sourceBlaster->FlushSourceBuffers();
							g_sourceBlaster->Start();

							//play the sound
							g_sourceBlaster->SubmitSourceBuffer(buffer7.xaBuffer());
							//}

							//start consuming audio in the source voice
							g_sourceHit->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceHit->Stop();
							g_sourceHit->FlushSourceBuffers();
							g_sourceHit->Start();

							//play the sound
							g_sourceHit->SubmitSourceBuffer(buffer6.xaBuffer());
							//}
						}
						Translation = XMMatrixTranslation(enemyXPos[i] += .00, enemyYPos[i], enemyZPos[i] -= .00);
						coll[i].setLocation(Point(enemyXPos[i] += .00, enemyYPos[i], enemyZPos[i] -= .00));
					}
					else{
						//Attack on random (moving so less likely to hit)
						if (randAttack % 77 == 0)
						{
							Player1.setHealth(Player1.getHealth() - 3);

							//start consuming audio in the source voice
							g_sourceBlaster->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceBlaster->Stop();
							g_sourceBlaster->FlushSourceBuffers();
							g_sourceBlaster->Start();

							//play the sound
							g_sourceBlaster->SubmitSourceBuffer(buffer7.xaBuffer());
							//}

							//start consuming audio in the source voice
							g_sourceHit->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceHit->Stop();
							g_sourceHit->FlushSourceBuffers();
							g_sourceHit->Start();

							//play the sound
							g_sourceHit->SubmitSourceBuffer(buffer6.xaBuffer());
							//}
						}
						Translation = XMMatrixTranslation(enemyXPos[i] += .01f, enemyYPos[i], enemyZPos[i] -= .01f);
						coll[i].setLocation(Point(enemyXPos[i] += .01f, enemyYPos[i], enemyZPos[i] -= .01f));
					}

				}
				//If playerX < enemyX, decrease enemyX, PlayerZ > enemyZ, increase enemyZ
				if (XMVectorGetX(mCam.getCamPosition()) < enemyXPos[i] && XMVectorGetZ(mCam.getCamPosition()) >= enemyZPos[i])
				{
					//Rotate enemy toward player
					if ((mCam.getCamYaw() >= enemyRot[i]))
					{
						Rotation = XMMatrixRotationY(enemyRot[i] += 0.01f);
						if (enemyRot[i] > 6.28f)
							enemyRot[i] = 0.0f;
						if (enemyRot[i] < 0.0f)
							enemyRot[i] = 6.28f;
					}
					else
					{
						Rotation = XMMatrixRotationY(enemyRot[i] -= 0.01f);
						if (enemyRot[i] > 6.28f)
							enemyRot[i] = 0.0f;
						if (enemyRot[i] < 0.0f)
							enemyRot[i] = 6.28f;
					}
					//If enemy is close to player, stop!
					if ((enemyXPos[i] - XMVectorGetX(mCam.getCamPosition()) <= 5 && enemyZPos[i] - XMVectorGetZ(mCam.getCamPosition()) <= 5)
						&& (enemyXPos[i] - XMVectorGetX(mCam.getCamPosition()) >= -5 && enemyZPos[i] - XMVectorGetZ(mCam.getCamPosition()) >= -5))
					{
						//Attack on random
						if (randAttack % 33 == 0)
						{
							Player1.setHealth(Player1.getHealth() - 3);

							//start consuming audio in the source voice
							g_sourceBlaster->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceBlaster->Stop();
							g_sourceBlaster->FlushSourceBuffers();
							g_sourceBlaster->Start();

							//play the sound
							g_sourceBlaster->SubmitSourceBuffer(buffer7.xaBuffer());
							//}

							//start consuming audio in the source voice
							g_sourceHit->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceHit->Stop();
							g_sourceHit->FlushSourceBuffers();
							g_sourceHit->Start();

							//play the sound
							g_sourceHit->SubmitSourceBuffer(buffer6.xaBuffer());
							//}
						}

						Translation = XMMatrixTranslation(enemyXPos[i] -= .00, enemyYPos[i], enemyZPos[i] += .00);
						coll[i].setLocation(Point(enemyXPos[i] -= .00, enemyYPos[i], enemyZPos[i] += .00));
					}
					else{
						//Attack on random (moving so less likely to hit)
						if (randAttack % 77 == 0)
						{
							Player1.setHealth(Player1.getHealth() - 3);

							//start consuming audio in the source voice
							g_sourceBlaster->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceBlaster->Stop();
							g_sourceBlaster->FlushSourceBuffers();
							g_sourceBlaster->Start();

							//play the sound
							g_sourceBlaster->SubmitSourceBuffer(buffer7.xaBuffer());
							//}

							//start consuming audio in the source voice
							g_sourceHit->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceHit->Stop();
							g_sourceHit->FlushSourceBuffers();
							g_sourceHit->Start();

							//play the sound
							g_sourceHit->SubmitSourceBuffer(buffer6.xaBuffer());
							//}
						}
						Translation = XMMatrixTranslation(enemyXPos[i] -= .01f, enemyYPos[i], enemyZPos[i] += .01f);
						coll[i].setLocation(Point(enemyXPos[i] -= .01f, enemyYPos[i], enemyZPos[i] += .01f));
					}

				}
				//If playerX < enemyX, decrease enemyX, PlayerZ < enemyZ, decrease enemyZ
				if (XMVectorGetX(mCam.getCamPosition()) < enemyXPos[i] && XMVectorGetZ(mCam.getCamPosition()) < enemyZPos[i])
				{
					//Rotate enemy toward player
					if ((mCam.getCamYaw() >= enemyRot[i]))
					{
						Rotation = XMMatrixRotationY(enemyRot[i] += 0.01f);
						if (enemyRot[i] > 6.28f)
							enemyRot[i] = 0.0f;
						if (enemyRot[i] < 0.0f)
							enemyRot[i] = 6.28f;
					}
					else
					{
						Rotation = XMMatrixRotationY(enemyRot[i] -= 0.01f);
						if (enemyRot[i] > 6.28f)
							enemyRot[i] = 0.0f;
						if (enemyRot[i] < 0.0f)
							enemyRot[i] = 6.28f;
					}
					if ((enemyXPos[i] - XMVectorGetX(mCam.getCamPosition()) <= 5 && enemyZPos[i] - XMVectorGetZ(mCam.getCamPosition()) <= 5)
						&& (enemyXPos[i] - XMVectorGetX(mCam.getCamPosition()) >= -5 && enemyZPos[i] - XMVectorGetZ(mCam.getCamPosition()) >= -5))
					{
						//Attack on random
						if (randAttack % 33 == 0)
						{
							Player1.setHealth(Player1.getHealth() - 3);

							//start consuming audio in the source voice
							g_sourceBlaster->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceBlaster->Stop();
							g_sourceBlaster->FlushSourceBuffers();
							g_sourceBlaster->Start();

							//play the sound
							g_sourceBlaster->SubmitSourceBuffer(buffer7.xaBuffer());
							//}

							//start consuming audio in the source voice
							g_sourceHit->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceHit->Stop();
							g_sourceHit->FlushSourceBuffers();
							g_sourceHit->Start();

							//play the sound
							g_sourceHit->SubmitSourceBuffer(buffer6.xaBuffer());
							//}
						}
						Translation = XMMatrixTranslation(enemyXPos[i] -= .00, enemyYPos[i], enemyZPos[i] -= .00);
						coll[i].setLocation(Point(enemyXPos[i] -= .00, enemyYPos[i], enemyZPos[i] -= .00));
					}
					else
					{
						//Attack on random (moving so less likely to hit)
						if (randAttack % 77 == 0)
						{
							Player1.setHealth(Player1.getHealth() - 3);

							//start consuming audio in the source voice
							g_sourceBlaster->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceBlaster->Stop();
							g_sourceBlaster->FlushSourceBuffers();
							g_sourceBlaster->Start();

							//play the sound
							g_sourceBlaster->SubmitSourceBuffer(buffer7.xaBuffer());
							//}

							//start consuming audio in the source voice
							g_sourceHit->Start();
							//simple message loop
							//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
							//{
							g_sourceHit->Stop();
							g_sourceHit->FlushSourceBuffers();
							g_sourceHit->Start();

							//play the sound
							g_sourceHit->SubmitSourceBuffer(buffer6.xaBuffer());
							//}
						}
						Translation = XMMatrixTranslation(enemyXPos[i] -= .01f, enemyYPos[i], enemyZPos[i] -= .01f);
						coll[i].setLocation(Point(enemyXPos[i] -= .01f, enemyYPos[i], enemyZPos[i] -= .01f));
					}
				}
				if (Player1.getHealth() <= 0)
				{
					Player1.setHealth(100);
					Player1.setLives(Player1.getLives() - 1);
		//start consuming audio in the source voice
		g_sourceRevive->Start();
		//simple message loop
		//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
		//{
		g_sourceRevive->Stop();
		g_sourceRevive->FlushSourceBuffers();
		g_sourceRevive->Start();

		//play the sound
		g_sourceRevive->SubmitSourceBuffer(buffer4.xaBuffer());
		//}
	}
	if (Player1.getLives() <= 0)
	{
		thePlayer.setDeath(true);
		//start consuming audio in the source voice
		g_sourceDead->Start();
		//simple message loop
		//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
		//{
		g_sourceDead->Stop();
		g_sourceDead->FlushSourceBuffers();
		g_sourceDead->Start();

		//play the sound
		g_sourceDead->SubmitSourceBuffer(buffer3.xaBuffer());
		//}
	}

	if (thePlayer.getDeath() == true)
	{
		if (MessageBox(0, L"You have been killed, would you like to restart?", L"You are dead", MB_YESNO | MB_ICONQUESTION) == IDNO)
			DestroyWindow(hwnd);
		else
		{
			thePlayer.Init(_settings);
			Player1.Init();
			PlayerWep.Init();
		}

				}
			}
			else {
				//OPTIMIZED AI MOVEMENT/ROTATION
				//Only change directions if number is divisible by 300
				if (randX % 300 == 0)
				{
					EMoveX[i] *= -1.0f;
				}
				if (randZ % 300 == 0)
					{
					EMoveZ[i] *= -1.0f;
					}
				//Only change rotation if number is divisible by 275
				if (randRot % 275 == 0)
					{
					ERot[i] *= -1.0f;
					}

				//Rotate enemy, don't let it go past full 360 degrees (2 pi)
				Rotation = XMMatrixRotationY(enemyRot[i] += ERot[i]);
						if (enemyRot[i] > 6.28f)
							enemyRot[i] = 0.0f;
						if (enemyRot[i] < 0.0f)
							enemyRot[i] = 6.28f;

				//Translate and update enemy and respective collision box
				Translation = XMMatrixTranslation(enemyXPos[i] += EMoveX[i], enemyYPos[i], enemyZPos[i] += EMoveZ[i]);
				coll[i].setLocation(Point(enemyXPos[i] += EMoveX[i], enemyYPos[i], enemyZPos[i] += EMoveZ[i]));
				
			}


			enemyArray[i].meshWorld = Rotation * Scale * Translation;
		}

	#pragma endregion EnemyAI
		//HUD
		if (meshArray[i].filename == L"HUD3.obj")
		{
			meshArray[i].meshWorld = XMMatrixIdentity();

			//Define cube1's world space matrix
			Rotation = XMMatrixRotationRollPitchYaw(mCam.getCamPitch(), mCam.getCamYaw(), 0.0f);
			//Rotation = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
			Scale = XMMatrixScaling(0.1f, 0.1f, 0.1f);
			Translation = XMMatrixTranslation(mCam.getsCamPosition().getX(), mCam.getsCamPosition().getY(), mCam.getsCamPosition().getZ());
			//Translation = XMMatrixTranslation(XMVectorGetX(mCam.getCamPosition()), XMVectorGetY(mCam.getCamPosition()) - 2.7, XMVectorGetZ(mCam.getCamPosition()));
			
		
			meshArray[i].meshWorld = Rotation * Scale * Translation;

		/*
			meshArray[i].meshWorld = XMMatrixIdentity();

			Rotation = XMMatrixRotationRollPitchYaw(mCam.getCamPitch(), mCam.getCamYaw(), 0);
			Scale = XMMatrixScaling(0.1f, 0.1f, 0.1f);
			Translation = XMMatrixTranslation(mCam.getsCamPosition().getX(), mCam.getsCamPosition().getY(), mCam.getsCamPosition().getZ());

			meshArray[i].meshWorld = Rotation * Scale * Translation;*/
		}

		if (meshArray[i].filename == L"ToT.obj")
		{
			meshArray[i].meshWorld = XMMatrixIdentity();

			Rotation = XMMatrixRotationY(0.0f);
		Scale = XMMatrixScaling(0.4f, 0.4f, 0.4f);
			Translation = XMMatrixTranslation(80.0f, 0.0f, -80.0f);

			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}

		//Temple of Time
		/*


		/*if (meshArray[i].filename == L"ground.obj")
		{
			meshArray[i].meshWorld = XMMatrixIdentity();

		Rotation = XMMatrixRotationY(3.14f);
		Scale = XMMatrixScaling(10.0f, 1.0f, 10.0f);
		Translation = XMMatrixTranslation(0.0f, -0.02f, 0.0f);

		meshArray[i].meshWorld = Rotation * Scale * Translation;
		}*/

			//Menu
			if (meshArray[i].filename == L"Menu.obj"){
				meshArray[i].meshWorld = XMMatrixIdentity();
			Rotation = XMMatrixRotationY(0.0f);
				Scale = XMMatrixScaling(0.1f, 0.1f, 0.1f);
				Translation = XMMatrixTranslation(10000.0f, 30000.0f, 10000.0f);
			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}
			//Moon
			if (meshArray[i].filename == L"Moon.obj")
	{
			meshArray[i].meshWorld = XMMatrixIdentity();
			Rotation = XMMatrixRotationY(0.0f);
			Scale = XMMatrixScaling(1.5f, 1.5f, 1.5f);
			Translation = XMMatrixTranslation(70.0f, moonHeight -= 0.06f, 60.0f);
			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}

		if (meshArray[i].filename == L"win.obj")
		{
			meshArray[i].meshWorld = XMMatrixIdentity();
			Rotation = XMMatrixRotationY(0.0f);
			Scale = XMMatrixScaling(0.1f, 0.1f, 0.1f);
			Translation = XMMatrixTranslation(winX, 3.0f, winZ);
			win.setLocation(Point(winX, 2.0f, winZ));
			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}

		if (meshArray[i].filename == L"spaceCompound.obj") {
			meshArray[i].meshWorld = XMMatrixIdentity();

			Rotation = XMMatrixRotationY(3.14f);
			Scale = XMMatrixScaling(0.25f, 0.75f, 0.25f);
			Translation = XMMatrixTranslation(62.0f, 17.0f, 60.0f);

			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}

		if (meshArray[i].filename == L"sa80.obj" || meshArray[i].filename == L"ak47.obj")
		{
			meshArray[i].meshWorld = XMMatrixIdentity();

			//kickback if shooted
			if (isShoot)
			{
				Rotation = XMMatrixRotationRollPitchYaw(mCam.getCamPitch() - 0.025, mCam.getCamYaw(), 0);
			}
			else
			{
			Rotation = XMMatrixRotationRollPitchYaw(mCam.getCamPitch(), mCam.getCamYaw(), 0);
			}

			if ((meshArray[i].filename == L"ak47.obj" && weaponSelect == 1) || (meshArray[i].filename == L"sa80.obj" && weaponSelect == 2))
			{
				Scale = XMMatrixScaling(0.1f, 0.1f, 0.1f);
			}
			else
			{
				Scale = XMMatrixScaling(0.0f, 0.0f, 0.0f);
			}
			Translation = XMMatrixTranslation(mCam.getsCamPosition().getX(), mCam.getsCamPosition().getY(), mCam.getsCamPosition().getZ());


			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}
		/*if (meshArray[i].filename == L"eclipse.obj")
		{
		Rotation = XMMatrixRotationY(ItemRot + 0.1f);
		if (ItemRot >= 6.28)
		ItemRot = 0;
		Scale = XMMatrixScaling(0.15f, 0.15f, 0.15f);
		Translation = XMMatrixTranslation(0.0f, 2.0f, 0.0f);
		meshArray[i].meshWorld = Rotation * Scale * Translation;
		}*/
		//Draw game items
		for (int j = 0; j < ITEMCOUNT; j++)
		{

			Rotation = XMMatrixRotationY(ItemRot += 0.001f);
			if (ItemRot >= 6.28)
				ItemRot = 0;
			Scale = XMMatrixScaling(0.05f, 0.1f, 0.05f);
			Translation = XMMatrixTranslation(itemX[j], itemY[j], itemZ[j]);
			itemArray[j].meshWorld = Rotation * Scale * Translation;
		}

		for (int j = 0; j < AMMOCOUNT; j++)
		{

			Rotation = XMMatrixRotationY(ammoRot += 0.001f);
			if (ammoRot >= 6.28)
				ammoRot = 0;
			Scale = XMMatrixScaling(0.05f, 0.05f, 0.05f);
			Translation = XMMatrixTranslation(ammoX[j], ammoY[j], ammoZ[j]);
			ammoArray[j].meshWorld = Rotation * Scale * Translation;
		}
	}

	if ((moonHeight / 2) - 15 <= 0.0f){
		thePlayer.setDeath(true);
		//start consuming audio in the source voice
		g_sourceDead->Start();
		//simple message loop
		//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
		//{
		g_sourceDead->Stop();
		g_sourceDead->FlushSourceBuffers();
		g_sourceDead->Start();

		//play the sound
		g_sourceDead->SubmitSourceBuffer(buffer3.xaBuffer());
		//}

		if (thePlayer.getDeath() == true)
		{
			if (MessageBox(0, L"The world is destroyed, you have failed", L"The sky has fallen", MB_OK | MB_ICONWARNING) == IDOK)
				DestroyWindow(hwnd);
		}
		}

	}

	///////////////**************new**************////////////////////
	/*Scale = XMMatrixScaling(0.04f, 0.04f, 0.04f);			// The model is a bit too large for our scene, so make it smaller
	Translation = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
	smilesWorld = Scale * Translation;*/
	///////////////**************new**************////////////////////

	//Spotlight stuff
	/*light.pos.x = XMVectorGetX(mCam.getCamPosition());
	light.pos.y = XMVectorGetY(mCam.getCamPosition());
	light.pos.z = XMVectorGetZ(mCam.getCamPosition());

	light.dir.x = XMVectorGetX(mCam.getCamTarget()) - light.pos.x;
	light.dir.y = XMVectorGetY(mCam.getCamTarget()) - light.pos.y;
	light.dir.z = XMVectorGetZ(mCam.getCamTarget()) - light.pos.z;*/
}

void SeniorPro::RenderText(std::wstring text, int inInt)
{
	//Release the D3D 11 Device
	keyedMutex11->ReleaseSync(0);

	//Use D3D10.1 device
	keyedMutex10->AcquireSync(0, 5);

	//Draw D2D content		
	D2DRenderTarget->BeginDraw();

	//Clear D2D Background
	D2DRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));

	//Create our string
	std::wostringstream printString;
		

	if (thePlayer.getDeath() == false)
	{
		printString <<
		L"  Health: " << Player1.getHealth()
			<< L"                                                                                                                                  Lives: " << Player1.getLives() << "\n"
			<< L"  Ammo: " << PlayerWep.getMagSize() << L"          Extra Mags: " << PlayerWep.getExtraClips()
			<< L"                                                                                                       Score: " << score << L"\n"
			<< "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
			//<< L"win x: " << winX - 125 << " win y  " << winZ - 125
			//<< L" player y: " << XMVectorGetY(mCam.getCamPosition()) 
			//<< L" player z: " << XMVectorGetZ(mCam.getCamPosition()) 

			<< L"  EnemyHeath: " << enemyStats[hitMe].getHealth() << L"\n"
			//144 = 72 hours, 96 = 48 hours, 48 = 24 hours
			<< L" " << (moonHeight / 2) - 15 << L" Hours Remain\n";
		//<< L"Enemy Picked: " << hitMe << L"\n"
		//<< L"Picked Dist: " << pickedDist << "\n"
		//<< L"Picked Dist: " << pickedDist2 << "\n"
		//<< L"Picked Dist: " << pickedDist3 << "\n"
		//<< L"Picked Dist: " << pickedDist4 << "\n"
		//<< L"Picked Dist: " << pickedDist5 << "\n"
		//<< L"Picked Dist: " << pickedDist6 << "\n"
		//<< L"Picked Dist: " << pickedDist7 << "\n"
		//<< L"Picked Dist: " << pickedDist8 << "\n"
		//<< L"Player Yaw: " << mCam.getCamYaw() << "\n"
		//<< L"Enemy Rot: " << enemyRot[1] << "\n"
		//<< L"Dist from enemy1: " << enemyXPos[1] - XMVectorGetX(mCam.getCamPosition()) << "\n";
		printText = printString.str();
		if (reloadBro == true)
		{
			printString <<
				L" OUTTA AMMO, RELOAD!!";
			printText = printString.str();
		}
	}

	//Set the Font Color
	D2D1_COLOR_F FontColor = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);

	//Set the brush color D2D will use to draw with
	Brush->SetColor(FontColor);

	//Create the D2D Render Area
	D2D1_RECT_F layoutRect = D2D1::RectF(0, 0, Width, Height);

	//Draw the Text
	D2DRenderTarget->DrawText(
		printText.c_str(),
		wcslen(printText.c_str()),
		TextFormat,
		layoutRect,
		Brush
		);

	D2DRenderTarget->EndDraw();

	//Release the D3D10.1 Device
	keyedMutex10->ReleaseSync(1);

	//Use the D3D11 Device
	keyedMutex11->AcquireSync(1, 5);

	//Use the shader resource representing the direct2d render target
	//to texture a square which is rendered in screen space so it
	//overlays on top of our entire scene. We use alpha blending so
	//that the entire background of the D2D render target is "invisible",
	//And only the stuff we draw with D2D will be visible (the text)

	//Set the blend state for D2D render target texture objects
	d3d11DevCon->OMSetBlendState(d2dTransparency, NULL, 0xffffffff);

	//Set d2d's pixel shader so lighting calculations are not done
	d3d11DevCon->PSSetShader(D2D_PS, 0, 0);

	//Set the d2d Index buffer
	d3d11DevCon->IASetIndexBuffer(d2dIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//Set the d2d vertex buffer
	d3d11DevCon->IASetVertexBuffers(0, 1, &d2dVertBuffer, &stride, &offset);

	//WVP = XMMatrixIdentity();
	XMMATRIX temp = XMMatrixIdentity();
	mCam.setWVP(temp, temp, temp);
	cbPerObj.World = XMMatrixTranspose(mCam.getWVP());
	cbPerObj.WVP = XMMatrixTranspose(mCam.getWVP());
	d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
	d3d11DevCon->PSSetShaderResources(0, 1, &d2dTexture);
	d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

	d3d11DevCon->RSSetState(CWcullMode);
	//Draw the second cube
	d3d11DevCon->DrawIndexed(6, 0, 0);
}

void SeniorPro::DrawScene()
{
	//Clear our render target and depth/stencil view
	float bgColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);
	d3d11DevCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	constbuffPerFrame.light = light;
	d3d11DevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &constbuffPerFrame, 0, 0);
	d3d11DevCon->PSSetConstantBuffers(0, 1, &cbPerFrameBuffer);

	//Set our Render Target
	d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	//Set the default blend state (no blending) for opaque objects
	d3d11DevCon->OMSetBlendState(0, 0, 0xffffffff);

	//Set Vertex and Pixel Shaders
	d3d11DevCon->VSSetShader(VS, 0, 0);
	d3d11DevCon->PSSetShader(PS, 0, 0);

	//Set the cubes index buffer
	d3d11DevCon->IASetIndexBuffer(squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//Set the cubes vertex buffer
	UINT stride = sizeof(Vertex::Vertex);
	UINT offset = 0;
	d3d11DevCon->IASetVertexBuffers(0, 1, &squareVertBuffer, &stride, &offset);

	//Set the WVP matrix and send it to the constant buffer in effect file
	mCam.setWVP(groundWorld, mCam.getCamView(), mCam.getCamProjection());
	cbPerObj.WVP = XMMatrixTranspose(mCam.getWVP());
	cbPerObj.World = XMMatrixTranspose(groundWorld);
	d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
	d3d11DevCon->PSSetShaderResources(0, 1, &CubesTexture);
	d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);
	d3d11DevCon->RSSetState(CCWcullMode);
	d3d11DevCon->DrawIndexed(NumFaces * 3, 0, 0);
	
	//Draw our model's NON-transparent subsets
	for (int i = 0; i < MESHCOUNT; i++)
	{
		drawModel(&meshArray[i], false);
	}
	for (int i = 0; i < ENEMYCOUNT; i++)
	{
		if (!enemyHit[i])
			if (enemyBox)
			drawModel(&enemyArray[i], false);

				drawMD5Model(&enemyArray[i]);
	}
	for (int i = 0; i < ITEMCOUNT; i++)
			{
		drawModel(&itemArray[i], false);
			}
	for (int i = 0; i < AMMOCOUNT; i++)
	{
		drawModel(&ammoArray[i], false);
	}

	XMMATRIX view, proj, world;

	// Construct the frustum.
	m_Frustum->ConstructFrustum(100.0f, proj, view);//mCam.getCamProjection(), mCam.getCamView());

	// Set the terrain shader parameters that it will use for rendering.
	m_TerrainShader->SetShaderParameters(d3d11DevCon, world, view, proj,//mCam.getWorld(), mCam.getCamView(), mCam.getCamProjection(),
		light.ambient, light.diffuse, light.dir, m_Terrain->GetTexture());

	// Render the terrain using the quad tree and terrain shader.
	m_QuadTree->Render(m_Frustum, d3d11DevCon, m_TerrainShader);

	/////Draw the Sky's Sphere//////
	//Set the spheres index buffer
	d3d11DevCon->IASetIndexBuffer(mCubemap->sphereIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//Set the spheres vertex buffer
	d3d11DevCon->IASetVertexBuffers(0, 1, &mCubemap->sphereVertBuffer, &stride, &offset);

	//Set the WVP matrix and send it to the constant buffer in effect file
	mCam.setWVP(sphereWorld, mCam.getCamView(), mCam.getCamProjection());
	cbPerObj.WVP = XMMatrixTranspose(mCam.getWVP());
	cbPerObj.World = XMMatrixTranspose(sphereWorld);
	d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
	//Send our skymap resource view to pixel shader
	d3d11DevCon->PSSetShaderResources(0, 1, &mCubemap->smrv);
	d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

	//Set the new VS and PS shaders
	d3d11DevCon->VSSetShader(mCubemap->SKYMAP_VS, 0, 0);
	d3d11DevCon->PSSetShader(mCubemap->SKYMAP_PS, 0, 0);
	//Set the new depth/stencil and RS states
	d3d11DevCon->OMSetDepthStencilState(DSLessEqual, 0);
	d3d11DevCon->RSSetState(RSCullNone);
	d3d11DevCon->DrawIndexed(mCubemap->getNumSphereFaces() * 3, 0, 0);

	//Set the default VS, PS shaders and depth/stencil state
	d3d11DevCon->VSSetShader(VS, 0, 0);
	d3d11DevCon->PSSetShader(PS, 0, 0);
	d3d11DevCon->OMSetDepthStencilState(NULL, 0);

	//Draw our model's TRANSPARENT subsets now
	for (int i = 0; i < MESHCOUNT; i++)
	{
		drawModel(&meshArray[i], true);
	}
	/*for (int i = 0; i < numEnemies; i++)
	{
		if (!enemyHit[i])
			drawModel(&enemyArray[i], true);
	}*/
	for (int i = 0; i < ITEMCOUNT; i++)
	{
		drawModel(&itemArray[i], true);
	}

	for (int i = 0; i < AMMOCOUNT; i++)
	{
		drawModel(&ammoArray[i], true);
	}
	if (graphicsCase == 2)
	{
	RenderText(L"Health: ", Player1.getHealth());
	RenderText(L"Lives: ", Player1.getLives());
	RenderText(L"Health: ", PlayerWep.getMagSize());
	RenderText(L"Enemy Picked Health %d", enemyStats[hitMe].getHealth());
	}
	//Present the backbuffer to the screen
	SwapChain->Present(0, 0);
}

void SeniorPro::DetectInput(double time)
{
	// collision for the heightmap
	float height;
	bool foundHeight;
	
	// Get the current position of the camera.
	XMVECTOR position = mCam.getCamPosition();

	// Get the height of the triangle that is directly underneath the given camera position.
	foundHeight = m_QuadTree->GetHeightAtPosition(XMVectorGetX(position), XMVectorGetZ(position), height);
	if (foundHeight)
	{
		// If there was a triangle under the camera then position the camera just above it by two units.
		mCam.setCamPosition(XMVectorGetX(position), height + 4.0f, XMVectorGetZ(position), 0.0f);
	}
	
	DIMOUSESTATE mouseCurrState;

	BYTE keyboardState[256];

	DIKeyboard->Acquire();
	DIMouse->Acquire();

	DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);

	DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
	bool flip = false;
	if (keyboardState[DIK_ESCAPE] & 0x80)
		PostMessage(hwnd, WM_DESTROY, 0, 0);

	float speed = 15.0f * time;
	if (keyboardState[DIK_M] & 0x80)
	{
		//start consuming audio in the source voice
		g_source->Start();

		//simple message loop
		//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
		//{
		g_source->Stop();
		g_source->FlushSourceBuffers();
		g_source->Start();

		//play the sound
		g_source->SubmitSourceBuffer(buffer.xaBuffer());
		//}
	}
	//Menu Screen
	if (graphicsCase == 1){
		//Play
		if (keyboardState[DIK_1] & 0X80)
		{
			graphicsCase = 2;
		}
		//Leaderboards
		if (keyboardState[DIK_2] & 0X80)
		{
			graphicsCase = 2;
		}
		//Quit
		if (keyboardState[DIK_3] & 0X80)
		{
			PostMessage(hwnd, WM_DESTROY, 0, 0);
		}

		if ((mouseCurrState.lX != mouseLastState.lX) || (mouseCurrState.lY != mouseLastState.lY))
		{
			//camYaw += mouseLastState.lX * 0.001f;
			mCam.setCamYaw(mCam.getCamYaw() + (mouseLastState.lX * 0.001f));

			if (mCam.getCamYaw() > 6.28f)
				mCam.setCamYaw(0.0f);
			if (mCam.getCamYaw() < 0.0f)
				mCam.setCamYaw(6.28f);
			//camPitch += mouseCurrState.lY * 0.001f;
			mCam.setCamPitch(mCam.getCamPitch() + (mouseLastState.lY * 0.001f));

			mouseLastState = mouseCurrState;
		}

		mCam.UpdateCamera();
	}
	if (graphicsCase == 2){
	for (int i = 0; i < ENEMYCOUNT; i++){
		if (coll[i].checkPointCollision(Point(XMVectorGetX(mCam.getCamPosition()), XMVectorGetY(mCam.getCamPosition()), XMVectorGetZ(mCam.getCamPosition())))){
			move = false;
			break;
			
		}
		else{
			move = true;
			
		}
	}

	for (int i = 0; i < ITEMCOUNT; i++){
		if (itemColl[i].checkPointCollision(Point(XMVectorGetX(mCam.getCamPosition()), XMVectorGetY(mCam.getCamPosition()), XMVectorGetZ(mCam.getCamPosition())))){
			score += 5;
			itemX[i] = 10000;
			itemZ[i] = 10000;
			itemColl[i].setLocation(Point(10000, 2.0f, 10000));
			break;

		}
		else{

		}
	}

	for (int i = 0; i < AMMOCOUNT; i++){
		if (ammoColl[i].checkPointCollision(Point(XMVectorGetX(mCam.getCamPosition()), XMVectorGetY(mCam.getCamPosition()), XMVectorGetZ(mCam.getCamPosition())))){
			PlayerWep.setExtraClips(3);
			ammoX[i] = 10000;
			ammoZ[i] = 10000;
			ammoColl[i].setLocation(Point(10000, 2.0f, 10000));
			break;

		}
		else{
			move = false;

		}
	}

	//Check for win condition
	if (win.checkPointCollision(Point(XMVectorGetX(mCam.getCamPosition()), XMVectorGetY(mCam.getCamPosition()), XMVectorGetZ(mCam.getCamPosition())))){
		score += 9001;
		winX = 100000;
		winZ = 100000;
	}

	//Check for collision and then allow for user to  move
	if (keyboardState[DIK_A] & 0x80 && pickedDist >= 0.5 && pickedDist2 >= 0.5 && pickedDist3 >= 0.5 && pickedDist4 >= 0.5 && pickedDist5 >= 0.5
		&& pickedDist6 >= 0.5 && pickedDist7 >= 0.5 && pickedDist8 >= 0.5 && pickedDist9 >= 0.5 && pickedDist10 >= 0.5)
	{
		//moveLeftRight -= speed;
		mCam.setMoveLeftRight(mCam.getMoveLeftRight() - speed);
		
	}
	if (keyboardState[DIK_D] & 0x80 && pickedDist >= 0.5 && pickedDist2 >= 0.5 && pickedDist3 >= 0.5 && pickedDist4 >= 0.5 && pickedDist5 >= 0.5
		&& pickedDist6 >= 0.5 && pickedDist7 >= 0.5 && pickedDist8 >= 0.5 && pickedDist9 >= 0.5 && pickedDist10 >= 0.5)
	{
		//moveLeftRight += speed;
		mCam.setMoveLeftRight(mCam.getMoveLeftRight() + speed);
	}
	if (keyboardState[DIK_W] & 0x80 && pickedDist >= 0.5 && pickedDist2 >= 0.5 && pickedDist3 >= 0.5 && pickedDist4 >= 0.5 && pickedDist5 >= 0.5
		&& pickedDist6 >= 0.5 && pickedDist7 >= 0.5 && pickedDist8 >= 0.5 && pickedDist9 >= 0.5 && pickedDist10 >= 0.5)
	{
		//moveBackForward += speed;
		mCam.setMoveBackForward(mCam.getMoveBackForward() + speed);
	}
	if (keyboardState[DIK_S] & 0x80)
	{
		//moveBackForward -= speed;
		mCam.setMoveBackForward(mCam.getMoveBackForward() - speed);
	}
	if (keyboardState[DIK_R] & 0x80)
	{
		if (PlayerWep.getExtraClips() > 0)
		{
		if (PlayerWep.getMagSize() < 8)
		{
			//start consuming audio in the source voice

			//simple message loop
			//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
			//{
			g_sourceReload->Stop();
			g_sourceReload->FlushSourceBuffers();
			g_sourceReload->Start();

			//play the sound
			g_sourceGun->SubmitSourceBuffer(buffer5.xaBuffer());
			//}
				PlayerWep.reload();
				PlayerWep.setExtraClips(-1);
			reloadBro = false;
		}
		}

	}
	if (keyboardState[DIK_E] & 0x80)
	{
		moveDoors = !moveDoors;

	}

	if (keyboardState[DIK_L] & 0x80)
	{
		//thePlayer.setDeath(true);
	}

	///////////////**************new**************////////////////////
	if (keyboardState[DIK_1] & 0X80)
	{
		weaponSelect = 1;
	}

	if (keyboardState[DIK_2] & 0X80)
	{
		weaponSelect = 2;
	}

	if (keyboardState[DIK_Y] & 0X80)
	{
		float timeFactor = 0.75f;	// You can speed up or slow down time by changing this
		for (int i = 0; i < ENEMYCOUNT; i++)
		{
			enemyArray[i].UpdateMD5Model(time*timeFactor, 0, d3d11DevCon);
		}
	}

	if (keyboardState[DIK_B] & 0X80)
	{
		enemyBox = !enemyBox;
	}
	///////////////**************new**************////////////////////

	if ((mouseCurrState.rgbButtons[0]))
	{
		//CHECK HERE
		//Gun
		if (PlayerWep.getMagSize() <= 0){
			reloadBro = true;
		}
		else{
			
			if (isShoot == false)
			{
			PlayerWep.setMagSize(PlayerWep.getMagSize() - 1);

			//start consuming audio in the source voice
			g_sourceGun->Start();
			//simple message loop
			//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
			//{
			g_sourceGun->Stop();
			g_sourceGun->FlushSourceBuffers();
			g_sourceGun->Start();

			//play the sound
			g_sourceGun->SubmitSourceBuffer(buffer2.xaBuffer());
			//}
			
			
			POINT mousePos;

			GetCursorPos(&mousePos);
			ScreenToClient(hwnd, &mousePos);

			int mousex = mousePos.x;
			int mousey = mousePos.y;

			float tempDist;
			float closestDist = FLT_MAX;
			int hitIndex;

			XMVECTOR prwsPos, prwsDir;
					pickRayVector(Width / 2, Height / 2, prwsPos, prwsDir);

				for (int i = 0; i < ENEMYCOUNT; i++)
			{
				if (enemyHit[i] == 0) //No need to check enemies already hit
				{
					//tempDist = pick(prwsPos, prwsDir, enemyArray[i].vertPosArray, enemyArray[i].vertIndexArray, enemyArray[i].meshWorld);
					/*for (int k = 0; k < MD5Model.numSubsets; k++)
						{
						for (int i = 0; i < MD5Model.subsets[k].vertices*/
					/*XMVECTOR h = XMVectorSet(1, 1, 1, 1);
					//XMVECTOR h = new XMVECTOR(enemyArray[i].MD5Model.subsets[0].vertices);
					XMMATRIX test;*/
					tempDist = pick(prwsPos, prwsDir, enemyArray[i].vertPosArray, enemyArray[i].vertIndexArray, enemyArray[i].meshWorld);
					if (tempDist < closestDist)
					{
						closestDist = tempDist;
						hitIndex = i;
					}
				}
			}

			if (closestDist < FLT_MAX)
			{
					hitMe = hitIndex;
					//Reduce that enemies health
					enemyStats[hitIndex].setHealth(enemyStats[hitIndex].getHealth() - 20);
					//If their health is less then 0 they are dead. remove them.
					if (enemyStats[hitIndex].getHealth() <= 0){
						// TRANSPORT

						enemies[hitIndex].setDeath(true);
						
				enemyHit[hitIndex] = 1;
				pickedDist = closestDist;
				score++;

						enemyXPos[hitIndex] = 1000;
						enemyZPos[hitIndex] = 1000;
			}
				}

			isShoot = true;
		}
		//CHECK HERE
		}
	}

		
	//CHECK HERE
	if (!mouseCurrState.rgbButtons[0])
	{
		isShoot = false;
	}
	//CHECK HERE
	else { flip = false; }

	if ((mouseCurrState.rgbButtons[1]))
	{
		//start consuming audio in the source voice
		g_sourceHit->Start();
		//simple message loop
		//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
		//{
		g_sourceHit->Stop();
		g_sourceHit->FlushSourceBuffers();
		g_sourceHit->Start();

		//play the sound
		g_sourceHit->SubmitSourceBuffer(buffer6.xaBuffer());
		//}
	}
	if ((mouseCurrState.lX != mouseLastState.lX) || (mouseCurrState.lY != mouseLastState.lY))
	{
		//camYaw += mouseLastState.lX * 0.001f;
		mCam.setCamYaw(mCam.getCamYaw() + (mouseLastState.lX * 0.001f));

		if (mCam.getCamYaw() > 6.28f)
			mCam.setCamYaw(0.0f);
		if (mCam.getCamYaw() < 0.0f)
			mCam.setCamYaw(6.28f);
		//camPitch += mouseCurrState.lY * 0.001f;
		mCam.setCamPitch(mCam.getCamPitch() + (mouseLastState.lY * 0.001f));

		mouseLastState = mouseCurrState;
	}



	mCam.UpdateCamera();
	//Best.updatePos(mCam.getsCamPosition(), mCam.getsCamTarget(), mCam.getsCamUp());

	// make a better following class
	//em.updatePos(Point(em.getpos().getX() - Best.getpos().getX(), em.getpos().getY(), 0.0f), Best.getpos(), em.getup());
	}
	return;
}

void SeniorPro::drawModel(Mesh* mesh, bool transparent)
{
	if (transparent)
	{
		//Draw our model's TRANSPARENT subsets now

		//Set our blend state

		d3d11DevCon->OMSetBlendState(Transparency, NULL, 0xffffffff);

		for (int i = 0; i < mesh->subsetCount; ++i)
		{
			//Set the grounds index buffer
			d3d11DevCon->IASetIndexBuffer(mesh->indexBuff, DXGI_FORMAT_R32_UINT, 0);
			//Set the grounds vertex buffer
			d3d11DevCon->IASetVertexBuffers(0, 1, &mesh->vertBuff, &stride, &offset);

			//Set the WVP matrix and send it to the constant buffer in effect file
			mCam.setWVP(mesh->meshWorld, mCam.getCamView(), mCam.getCamProjection());
			cbPerObj.WVP = XMMatrixTranspose(mCam.getWVP());
			cbPerObj.World = XMMatrixTranspose(mesh->meshWorld);
			cbPerObj.difColor = material[mesh->subsetTexture[i]].difColor;
			cbPerObj.hasTexture = material[mesh->subsetTexture[i]].hasTexture;
			cbPerObj.hasNormMap = material[mesh->subsetTexture[i]].hasNormMap;
			d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
			d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
			d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerObjectBuffer);
			if (material[mesh->subsetTexture[i]].hasTexture)
				d3d11DevCon->PSSetShaderResources(0, 1, &mesh->meshSRV[material[mesh->subsetTexture[i]].texArrayIndex]);
			if (material[mesh->subsetTexture[i]].hasNormMap)
				d3d11DevCon->PSSetShaderResources(1, 1, &mesh->meshSRV[material[mesh->subsetTexture[i]].normMapTexArrayIndex]);
			d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

			d3d11DevCon->RSSetState(RSCullNone);
			int indexStart = mesh->subsetIndexStart[i];
			int indexDrawAmount = mesh->subsetIndexStart[i + 1] - mesh->subsetIndexStart[i];
			if (material[mesh->subsetTexture[i]].transparent)
				d3d11DevCon->DrawIndexed(indexDrawAmount, indexStart, 0);
		}
	}
	else
	{
		//Draw our model's NON-transparent subsets
		for (int i = 0; i < mesh->subsetCount; ++i)
		{
			//Set the grounds index buffer
			d3d11DevCon->IASetIndexBuffer(mesh->indexBuff, DXGI_FORMAT_R32_UINT, 0);
			//Set the grounds vertex buffer
			d3d11DevCon->IASetVertexBuffers(0, 1, &mesh->vertBuff, &stride, &offset);

			//Set the WVP matrix and send it to the constant buffer in effect file
			mCam.setWVP(mesh->meshWorld, mCam.getCamView(), mCam.getCamProjection());
			cbPerObj.WVP = XMMatrixTranspose(mCam.getWVP());
			cbPerObj.World = XMMatrixTranspose(mesh->meshWorld);
			cbPerObj.difColor = material[mesh->subsetTexture[i]].difColor;
			cbPerObj.hasTexture = material[mesh->subsetTexture[i]].hasTexture;
			cbPerObj.hasNormMap = material[mesh->subsetTexture[i]].hasNormMap;
			d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
			d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
			d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerObjectBuffer);
			if (material[mesh->subsetTexture[i]].hasTexture)
				d3d11DevCon->PSSetShaderResources(0, 1, &mesh->meshSRV[material[mesh->subsetTexture[i]].texArrayIndex]);
			if (material[mesh->subsetTexture[i]].hasNormMap)
				d3d11DevCon->PSSetShaderResources(1, 1, &mesh->meshSRV[material[mesh->subsetTexture[i]].normMapTexArrayIndex]);
			d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

			d3d11DevCon->RSSetState(RSCullNone);
			int indexStart = mesh->subsetIndexStart[i];
			int indexDrawAmount = mesh->subsetIndexStart[i + 1] - mesh->subsetIndexStart[i];
			if (!material[mesh->subsetTexture[i]].transparent)
				d3d11DevCon->DrawIndexed(indexDrawAmount, indexStart, 0);
		}
	}
}

void SeniorPro::drawMD5Model(Mesh* mesh)
{
	for (int i = 0; i < mesh->MD5Model.numSubsets; i++)
	{
		//Set the grounds index buffer
		d3d11DevCon->IASetIndexBuffer(mesh->MD5Model.subsets[i].indexBuff, DXGI_FORMAT_R32_UINT, 0);
		//Set the grounds vertex buffer
		d3d11DevCon->IASetVertexBuffers(0, 1, &mesh->MD5Model.subsets[i].vertBuff, &stride, &offset);

		//Set the WVP matrix and send it to the constant buffer in effect file
		mCam.setWVP(mesh->meshWorld, mCam.getCamView(), mCam.getCamProjection());
		cbPerObj.WVP = XMMatrixTranspose(mCam.getWVP());
		cbPerObj.World = XMMatrixTranspose(mesh->meshWorld);
		cbPerObj.hasTexture = true;		// We'll assume all md5 subsets have textures
		cbPerObj.hasNormMap = false;	// We'll also assume md5 models have no normal map (easy to change later though)
		d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
		d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
		d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerObjectBuffer);
		d3d11DevCon->PSSetShaderResources(0, 1, &mesh->meshSRV[mesh->MD5Model.subsets[i].texArrayIndex]);
		d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

		d3d11DevCon->RSSetState(RSCullNone);
		d3d11DevCon->DrawIndexed(mesh->MD5Model.subsets[i].indices.size(), 0, 0);
	}

}


void SeniorPro::pickRayVector(float mouseX, float mouseY, XMVECTOR& pickRayInWorldSpacePos, XMVECTOR& pickRayInWorldSpaceDir)
{
	XMVECTOR pickRayInViewSpaceDir = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR pickRayInViewSpacePos = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	float PRVecX, PRVecY, PRVecZ;

	//Transform 2D pick position on screen space to 3D ray in View space

	XMMATRIX camProjection = mCam.getCamProjection();
	PRVecX = (((2.0f * mouseX) / ClientWidth) - 1) / camProjection(0, 0);
	PRVecY = -(((2.0f * mouseY) / ClientHeight) - 1) / camProjection(1, 1);
	PRVecZ = 1.0f;	//View space's Z direction ranges from 0 to 1, so we set 1 since the ray goes "into" the screen

	pickRayInViewSpaceDir = XMVectorSet(PRVecX, PRVecY, PRVecZ, 0.0f);

	//Uncomment this line if you want to use the center of the screen (client area)
	//to be the point that creates the picking ray (eg. first person shooter)
	//pickRayInViewSpaceDir = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// Transform 3D Ray from View space to 3D ray in World space
	XMMATRIX pickRayToWorldSpaceMatrix;
	XMVECTOR matInvDeter;	//We don't use this, but the xna matrix inverse function requires the first parameter to not be null

	pickRayToWorldSpaceMatrix = XMMatrixInverse(&matInvDeter, mCam.getCamView());	//Inverse of View Space matrix is World space matrix

	pickRayInWorldSpacePos = XMVector3TransformCoord(pickRayInViewSpacePos, pickRayToWorldSpaceMatrix);
	pickRayInWorldSpaceDir = XMVector3TransformNormal(pickRayInViewSpaceDir, pickRayToWorldSpaceMatrix);
}

float SeniorPro::pick(XMVECTOR pickRayInWorldSpacePos,
	XMVECTOR pickRayInWorldSpaceDir,
	std::vector<XMFLOAT3>& vertPosArray,
	std::vector<DWORD>& indexPosArray,
	XMMATRIX& worldSpace)
{
	//Loop through each triangle in the object
	for (int i = 0; i < indexPosArray.size() / 3; i++)
	{
		//Triangle's vertices V1, V2, V3
		XMVECTOR tri1V1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR tri1V2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR tri1V3 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		//Temporary 3d floats for each vertex
		XMFLOAT3 tV1, tV2, tV3;

		//Get triangle 
		tV1 = vertPosArray[indexPosArray[(i * 3) + 0]];
		tV2 = vertPosArray[indexPosArray[(i * 3) + 1]];
		tV3 = vertPosArray[indexPosArray[(i * 3) + 2]];

		tri1V1 = XMVectorSet(tV1.x, tV1.y, tV1.z, 0.0f);
		tri1V2 = XMVectorSet(tV2.x, tV2.y, tV2.z, 0.0f);
		tri1V3 = XMVectorSet(tV3.x, tV3.y, tV3.z, 0.0f);

		//Transform the vertices to world space
		tri1V1 = XMVector3TransformCoord(tri1V1, worldSpace);
		tri1V2 = XMVector3TransformCoord(tri1V2, worldSpace);
		tri1V3 = XMVector3TransformCoord(tri1V3, worldSpace);

		//Find the normal using U, V coordinates (two edges)
		XMVECTOR U = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR V = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR faceNormal = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		U = tri1V2 - tri1V1;
		V = tri1V3 - tri1V1;

		//Compute face normal by crossing U, V
		faceNormal = XMVector3Cross(U, V);

		faceNormal = XMVector3Normalize(faceNormal);

		//Calculate a point on the triangle for the plane equation
		XMVECTOR triPoint = tri1V1;

		//Get plane equation ("Ax + By + Cz + D = 0") Variables
		float tri1A = XMVectorGetX(faceNormal);
		float tri1B = XMVectorGetY(faceNormal);
		float tri1C = XMVectorGetZ(faceNormal);
		float tri1D = (-tri1A*XMVectorGetX(triPoint) - tri1B*XMVectorGetY(triPoint) - tri1C*XMVectorGetZ(triPoint));

		//Now we find where (on the ray) the ray intersects with the triangles plane
		float ep1, ep2, t = 0.0f;
		float planeIntersectX, planeIntersectY, planeIntersectZ = 0.0f;
		XMVECTOR pointInPlane = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		ep1 = (XMVectorGetX(pickRayInWorldSpacePos) * tri1A) + (XMVectorGetY(pickRayInWorldSpacePos) * tri1B) + (XMVectorGetZ(pickRayInWorldSpacePos) * tri1C);
		ep2 = (XMVectorGetX(pickRayInWorldSpaceDir) * tri1A) + (XMVectorGetY(pickRayInWorldSpaceDir) * tri1B) + (XMVectorGetZ(pickRayInWorldSpaceDir) * tri1C);

		//Make sure there are no divide-by-zeros
		if (ep2 != 0.0f)
			t = -(ep1 + tri1D) / (ep2);

		if (t > 0.0f)    //Make sure you don't pick objects behind the camera
		{
			//Get the point on the plane
			planeIntersectX = XMVectorGetX(pickRayInWorldSpacePos) + XMVectorGetX(pickRayInWorldSpaceDir) * t;
			planeIntersectY = XMVectorGetY(pickRayInWorldSpacePos) + XMVectorGetY(pickRayInWorldSpaceDir) * t;
			planeIntersectZ = XMVectorGetZ(pickRayInWorldSpacePos) + XMVectorGetZ(pickRayInWorldSpaceDir) * t;

			pointInPlane = XMVectorSet(planeIntersectX, planeIntersectY, planeIntersectZ, 0.0f);

			//Call function to check if point is in the triangle
			if (PointInTriangle(tri1V1, tri1V2, tri1V3, pointInPlane))
			{
				//Return the distance to the hit, so you can check all the other pickable objects in your scene
				//and choose whichever object is closest to the camera
				return t / 2.0f;
			}
		}
	}
	//return the max float value (near infinity) if an object was not picked
	return FLT_MAX;
}

bool SeniorPro::PointInTriangle(XMVECTOR& triV1, XMVECTOR& triV2, XMVECTOR& triV3, XMVECTOR& point)
{
	//To find out if the point is inside the triangle, we will check to see if the point
	//is on the correct side of each of the triangles edges.

	XMVECTOR cp1 = XMVector3Cross((triV3 - triV2), (point - triV2));
	XMVECTOR cp2 = XMVector3Cross((triV3 - triV2), (triV1 - triV2));
	if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
	{
		cp1 = XMVector3Cross((triV3 - triV1), (point - triV1));
		cp2 = XMVector3Cross((triV3 - triV1), (triV2 - triV1));
		if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
		{
			cp1 = XMVector3Cross((triV2 - triV1), (point - triV1));
			cp2 = XMVector3Cross((triV2 - triV1), (triV3 - triV1));
			if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
			{
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	return false;
}