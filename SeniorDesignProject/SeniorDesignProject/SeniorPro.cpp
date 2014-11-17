#include "d3dApp.h"
#include "CameraMain.h"
#include "VertexMain.h"
#include "Cubemap.h"
#include "Mesh.h"
#include "Collision.h"

#define MESHCOUNT 2

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

	void pickRayVector(float mouseX, float mouseY, XMVECTOR& pickRayInWorldSpacePos, XMVECTOR& pickRayInWorldSpaceDir);
	float pick(XMVECTOR pickRayInWorldSpacePos,
		XMVECTOR pickRayInWorldSpaceDir,
		std::vector<XMFLOAT3>& vertPosArray,
		std::vector<DWORD>& indexPosArray,
		XMMATRIX& worldSpace);
	bool PointInTriangle(XMVECTOR& triV1, XMVECTOR& triV2, XMVECTOR& triV3, XMVECTOR& point);

	///////////////**************new**************////////////////////
	//LoadMD5Model() function prototype
	bool LoadMD5Model(std::wstring filename,
		Struct::Model3D& MD5Model,
		std::vector<ID3D11ShaderResourceView*>& shaderResourceViewArray,
		std::vector<std::wstring> texFileNameArray);
	///////////////**************new**************////////////////////

	///////////////**************new**************////////////////////
	bool LoadMD5Anim(std::wstring filename, Struct::Model3D& MD5Model);

	void UpdateMD5Model(Struct::Model3D& MD5Model, float deltaTime, int animation);
	///////////////**************new**************////////////////////

private:
	CameraMain mCam;

	Collision coll[20];
	bool move;

	Cubemap* mCubemap;

	Mesh meshArray[MESHCOUNT];

	///////////////**************new**************////////////////////
	XMMATRIX smilesWorld;
	Struct::Model3D NewMD5Model;

	//Textures and material variables, used for all mesh's loaded
	//CHANGE to using MESH class, make it MD5 compatible
	std::vector<ID3D11ShaderResourceView*> meshSRV;
	std::vector<std::wstring> textureNameArray;
	///////////////**************new**************////////////////////

	XMMATRIX groundWorld;
	XMMATRIX sphereWorld;

	XMMATRIX Rotation;
	XMMATRIX Scale;
	XMMATRIX Translation;
	float rot = 0.01f;

	UINT stride = sizeof(Vertex::Vertex);
	UINT offset = 0;

	Mesh enemyArray[20];
	int* enemyHit = new int[20];
	int numEnemies = 20;

};
//run initializemainwindow
//Sound Init
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


//Sound stuff
Wave buffer; //Music
Wave buffer2; //gunshot
Wave buffer3; //dead
Wave buffer4; //revive
Wave buffer5; //reload
Wave buffer6; //bullethit

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
	mCam.setCamPosition(0.0f, 5.0f, -8.0f, 0.0f);
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

	//MD5 releasing, will be in Mesh class later
	///////////////**************new**************////////////////////
	for (int i = 0; i < NewMD5Model.numSubsets; i++)
	{
		NewMD5Model.subsets[i].indexBuff->Release();
		NewMD5Model.subsets[i].vertBuff->Release();
	}
	///////////////**************new**************////////////////////
};

bool SeniorPro::InitScene()
{
	//Init hit person
	hitMe = 1;
	InitD2DScreenTexture();

	// Create cubemap
	mCubemap = new Cubemap(d3d11Device);

	if (!meshArray[0].LoadObjModel(L"ground.obj", material, true, true, d3d11Device, SwapChain))
		return false;
	if (!meshArray[1].LoadObjModel(L"spaceCompound.obj", material, true, false, d3d11Device, SwapChain))
		return false;
	//Enemy.obj, DoorLeft.obj, DoorRight.obj

	for (int i = 0; i < numEnemies; i++)
	{
		if (!enemyArray[i].LoadObjModel(L"Enemy.obj", material, true, false, d3d11Device, SwapChain))
			return false;
	}

	///////////////**************new**************////////////////////
	if (!LoadMD5Model(L"boy.md5mesh", NewMD5Model, meshSRV, textureNameArray))
		return false;
	///////////////**************new**************////////////////////

	///////////////**************new**************////////////////////	
	if (!LoadMD5Anim(L"boy.md5anim", NewMD5Model))
		return false;
	///////////////**************new**************////////////////////

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

	//Create the vertex buffer
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
	};

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * 2 * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = indices;
	d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &squareIndexBuffer);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex::Vertex) * 4;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = v;
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

	float enemyXPos = -30.0f;
	float enemyZPos = 60.0f;
	float exadd = 0.0f;
	float ezadd = 0.0f;

	for (int i = 0; i < numEnemies; i++)
	{
		enemyHit[i] = 0;

		//set the loaded enemy's world space
		enemyArray[i].meshWorld = XMMatrixIdentity();

		exadd++;

		if (exadd == 10)
		{
			ezadd -= 1.0f;
			exadd = 0;
		}

		Rotation = XMMatrixRotationY(3.14f);
		Scale = XMMatrixScaling(0.15f, 0.15f, 0.15f);
		Translation = XMMatrixTranslation(enemyXPos + exadd*10.0f, 2.0f, enemyZPos + ezadd*10.0f);
		coll[i].setLocation(Point(enemyXPos + exadd*10.0f, 2.0f, enemyZPos + ezadd*10.0f));
		coll[i].setheight(3.0f);
		coll[i].setlength(3.0f);
		coll[i].setwidth(3.0f);
		enemyArray[i].meshWorld = Rotation * Scale * Translation;
	}

	return true;
}

void SeniorPro::UpdateScene(double time)
{

	float tempDist;
	float tempDist2;
	float tempDist3;
	float tempDist4;
	float tempDist5;
	float tempDist6;
	float tempDist7;
	float tempDist8;
	float tempDist9;
	float tempDist10;

	float closestDist = FLT_MAX;
	int hitIndex;
	//Get picking 
	XMVECTOR prwsPos, prwsDir, prwsPos2, prwsDir2, prwsPos3, prwsDir3, prwsPos4, prwsDir4, prwsPos5, prwsDir5;
	pickRayVector(0, 0, prwsPos, prwsDir);
	pickRayVector((Width / 2 - 1), 0, prwsPos2, prwsDir2);
	pickRayVector(((Width / -2) + 1), 0, prwsPos3, prwsDir3);
	pickRayVector(0, (Height / 2 - 1), prwsPos4, prwsDir4);
	pickRayVector(0, ((Height / -2) + 1), prwsPos5, prwsDir5);
	for (int i = 0; i < numEnemies; i++)
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
	tempDist6 = pick(prwsPos, prwsDir, meshArray[1].vertPosArray, meshArray[1].vertIndexArray, meshArray[1].meshWorld);
	tempDist7 = pick(prwsPos2, prwsDir2, meshArray[1].vertPosArray, meshArray[1].vertIndexArray, meshArray[1].meshWorld);
	tempDist8 = pick(prwsPos3, prwsDir3, meshArray[1].vertPosArray, meshArray[1].vertIndexArray, meshArray[1].meshWorld);
	tempDist9 = pick(prwsPos4, prwsDir4, meshArray[1].vertPosArray, meshArray[1].vertIndexArray, meshArray[1].meshWorld);
	tempDist10 = pick(prwsPos5, prwsDir5, meshArray[1].vertPosArray, meshArray[1].vertIndexArray, meshArray[1].meshWorld);

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

	if (Player1.getHealth() == 0)
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
	//Reset cube1World
	groundWorld = XMMatrixIdentity();

	//Define cube1's world space matrix
	Scale = XMMatrixScaling(500.0f, 10.0f, 500.0f);
	Translation = XMMatrixTranslation(0.0f, 10.0f, 0.0f);

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

	// Mesh Array
	for (int i = 0; i < MESHCOUNT; i++)
	{
		if (meshArray[i].filename == L"spaceCompound.obj")
		
		if (i == 2)
		{
			meshArray[i].meshWorld = XMMatrixIdentity();
			randX = rand() % 10;
			randZ = rand() % 10;
			//Define cube1's world space matrix
			Rotation = XMMatrixRotationY(3.14f);
			Scale = XMMatrixScaling(0.25f, 0.25f, 0.25f);
			Translation = XMMatrixTranslation(0.0f+ randX, 0.0f, 0.0f + randZ);

			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}
		if (i == 1)
		{
			meshArray[i].meshWorld = XMMatrixIdentity();

			Rotation = XMMatrixRotationY(3.14f);
			Scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
			Translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}
		if (meshArray[i].filename == L"ground.obj")
		{
			meshArray[i].meshWorld = XMMatrixIdentity();

			Rotation = XMMatrixRotationY(3.14f);
			Scale = XMMatrixScaling(10.0f, 1.0f, 10.0f);
			Translation = XMMatrixTranslation(0.0f, -0.02f, 0.0f);

			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}
	}

	///////////////**************new**************////////////////////
	Scale = XMMatrixScaling(0.04f, 0.04f, 0.04f);			// The model is a bit too large for our scene, so make it smaller
	Translation = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
	smilesWorld = Scale * Translation;
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
			L"Health: " << Player1.getHealth() << "\n"
			<< L"Ammo: " << PlayerWep.getMagSize() << "\n"
			<< L"Lives: " << Player1.getLives() << "\n"
			<< L"player x: " << XMVectorGetX(mCam.getCamPosition()) << "\n"
			<< L"player y: " << XMVectorGetY(mCam.getCamPosition()) << "\n"
			<< L"player z: " << XMVectorGetZ(mCam.getCamPosition()) << "\n"
			<< L"Lives: " << Player1.getLives() << "\n"
			<< L"Score: " << score << L"\n"
			<< L"EnemyHeath: " << enemyStats[hitMe].getHealth() << L"\n"
			<< L"Enemy Picked: " << hitMe << L"\n"
			//<< L"Picked Dist: " << pickedDist << "\n"
			//<< L"Picked Dist: " << pickedDist2 << "\n"
			//<< L"Picked Dist: " << pickedDist3 << "\n"
			//<< L"Picked Dist: " << pickedDist4 << "\n"
			//<< L"Picked Dist: " << pickedDist5 << "\n"
			<< L"Picked Dist: " << pickedDist6 << "\n"
			<< L"Picked Dist: " << pickedDist7 << "\n"
			<< L"Picked Dist: " << pickedDist8 << "\n"
			<< L"Picked Dist: " << pickedDist9 << "\n"
			<< L"Picked Dist: " << pickedDist10 << "\n";
		printText = printString.str();
		if (reloadBro == true)
		{
			printString <<
				L"OUTTA AMMO, RELOAD!!";
			printText = printString.str();
		}
	}
	else {
		printString <<
			L"YOU ARE DEAD! HA...HAHAHA!!: ";
		printText = printString.str();
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
	//d3d11DevCon->DrawIndexed( 6, 0, 0 );

	///////////////**************new**************////////////////////
	///***Draw MD5 Model***///
	for (int i = 0; i < NewMD5Model.numSubsets; i++)
	{
		//Set the grounds index buffer
		d3d11DevCon->IASetIndexBuffer(NewMD5Model.subsets[i].indexBuff, DXGI_FORMAT_R32_UINT, 0);
		//Set the grounds vertex buffer
		d3d11DevCon->IASetVertexBuffers(0, 1, &NewMD5Model.subsets[i].vertBuff, &stride, &offset);

		//Set the WVP matrix and send it to the constant buffer in effect file
		mCam.setWVP(smilesWorld, mCam.getCamView(), mCam.getCamProjection());
		cbPerObj.WVP = XMMatrixTranspose(mCam.getWVP());
		cbPerObj.World = XMMatrixTranspose(smilesWorld);
		cbPerObj.hasTexture = true;		// We'll assume all md5 subsets have textures
		cbPerObj.hasNormMap = false;	// We'll also assume md5 models have no normal map (easy to change later though)
		d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
		d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
		d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerObjectBuffer);
		d3d11DevCon->PSSetShaderResources(0, 1, &meshSRV[NewMD5Model.subsets[i].texArrayIndex]);
		d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

		d3d11DevCon->RSSetState(RSCullNone);
		d3d11DevCon->DrawIndexed(NewMD5Model.subsets[i].indices.size(), 0, 0);
	}
	///////////////**************new**************////////////////////

	//Draw our model's NON-transparent subsets
	for (int i = 0; i < MESHCOUNT; i++)
	{
		drawModel(&meshArray[i], false);
	}
	for (int i = 0; i < numEnemies; i++)
	{
		if (!enemyHit[i])
			drawModel(&enemyArray[i], false);
	}

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
	for (int i = 0; i < numEnemies; i++)
	{
		if (!enemyHit[i])
			drawModel(&enemyArray[i], true);
	}

	RenderText(L"Health: ", Player1.getHealth());
	RenderText(L"Lives: ", Player1.getLives());
	RenderText(L"Health: ", PlayerWep.getMagSize());
	RenderText(L"Enemy Picked Health %d", enemyStats[hitMe].getHealth());
	//Present the backbuffer to the screen
	SwapChain->Present(0, 0);
}

void SeniorPro::DetectInput(double time)
{
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

	for (int i = 0; i < 20; i++){
		if (coll[i].checkPointCollision(Point(XMVectorGetX(mCam.getCamPosition()), XMVectorGetY(mCam.getCamPosition()), XMVectorGetZ(mCam.getCamPosition())))){
			move = false;
			break;
			
		}
		else{
			move = true;
			
		}
		
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
	if (keyboardState[DIK_S] & 0x80 && move)
	{
		//moveBackForward -= speed;
		mCam.setMoveBackForward(mCam.getMoveBackForward() - speed);
	}
	if (keyboardState[DIK_R] & 0x80)
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
			PlayerWep.setMagSize(8);
			reloadBro = false;
		}

	}
	if (keyboardState[DIK_L] & 0x80)
	{
		thePlayer.setDeath(true);
	}

	///////////////**************new**************////////////////////
	if (keyboardState[DIK_Y] & 0X80)
	{
		float timeFactor = 1.0f;	// You can speed up or slow down time by changing this
		UpdateMD5Model(NewMD5Model, time*timeFactor, 0);
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
				pickRayVector(Width/2, Height/2, prwsPos, prwsDir);

			for (int i = 0; i < numEnemies; i++)
				{
				if (enemyHit[i] == 0) //No need to check enemies already hit
					{
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
						enemies[hitIndex].setDeath(true);
						
				enemyHit[hitIndex] = 1;
						pickedDist = closestDist;
						score++;
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
		Player1.setHealth(Player1.getHealth() - 2);
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

		//camPitch += mouseCurrState.lY * 0.001f;
		mCam.setCamPitch(mCam.getCamPitch() + (mouseLastState.lY * 0.001f));

		mouseLastState = mouseCurrState;
	}

	mCam.UpdateCamera();

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

///////////////**************new**************////////////////////
bool SeniorPro::LoadMD5Model(std::wstring filename,
	Struct::Model3D& MD5Model,
	std::vector<ID3D11ShaderResourceView*>& shaderResourceViewArray,
	std::vector<std::wstring> texFileNameArray)
{
	std::wifstream fileIn(filename.c_str());		// Open file

	std::wstring checkString;						// Stores the next string from our file

	if (fileIn)										// Check if the file was opened
	{
		while (fileIn)								// Loop until the end of the file is reached
		{
			fileIn >> checkString;					// Get next string from file

			if (checkString == L"MD5Version")		// Get MD5 version (this function supports version 10)
			{
				/*fileIn >> checkString;
				MessageBox(0, checkString.c_str(),	//display message
				L"MD5Version", MB_OK);*/
			}
			else if (checkString == L"commandline")
			{
				std::getline(fileIn, checkString);	// Ignore the rest of this line
			}
			else if (checkString == L"numJoints")
			{
				fileIn >> MD5Model.numJoints;		// Store number of joints
			}
			else if (checkString == L"numMeshes")
			{
				fileIn >> MD5Model.numSubsets;		// Store number of meshes or subsets which we will call them
			}
			else if (checkString == L"joints")
			{
				Struct::Joint tempJoint;

				fileIn >> checkString;				// Skip the "{"

				for (int i = 0; i < MD5Model.numJoints; i++)
				{
					fileIn >> tempJoint.name;		// Store joints name
					// Sometimes the names might contain spaces. If that is the case, we need to continue
					// to read the name until we get to the closing " (quotation marks)
					if (tempJoint.name[tempJoint.name.size() - 1] != '"')
					{
						wchar_t checkChar;
						bool jointNameFound = false;
						while (!jointNameFound)
						{
							checkChar = fileIn.get();

							if (checkChar == '"')
								jointNameFound = true;

							tempJoint.name += checkChar;
						}
					}

					fileIn >> tempJoint.parentID;	// Store Parent joint's ID

					fileIn >> checkString;			// Skip the "("

					// Store position of this joint (swap y and z axis if model was made in RH Coord Sys)
					fileIn >> tempJoint.pos.x >> tempJoint.pos.z >> tempJoint.pos.y;

					fileIn >> checkString >> checkString;	// Skip the ")" and "("

					// Store orientation of this joint
					fileIn >> tempJoint.orientation.x >> tempJoint.orientation.z >> tempJoint.orientation.y;

					// Remove the quotation marks from joints name
					tempJoint.name.erase(0, 1);
					tempJoint.name.erase(tempJoint.name.size() - 1, 1);

					// Compute the w axis of the quaternion (The MD5 model uses a 3D vector to describe the
					// direction the bone is facing. However, we need to turn this into a quaternion, and the way
					// quaternions work, is the xyz values describe the axis of rotation, while the w is a value
					// between 0 and 1 which describes the angle of rotation)
					float t = 1.0f - (tempJoint.orientation.x * tempJoint.orientation.x)
						- (tempJoint.orientation.y * tempJoint.orientation.y)
						- (tempJoint.orientation.z * tempJoint.orientation.z);
					if (t < 0.0f)
					{
						tempJoint.orientation.w = 0.0f;
					}
					else
					{
						tempJoint.orientation.w = -sqrtf(t);
					}

					std::getline(fileIn, checkString);		// Skip rest of this line

					MD5Model.joints.push_back(tempJoint);	// Store the joint into this models joint vector
				}

				fileIn >> checkString;					// Skip the "}"
			}
			else if (checkString == L"mesh")
			{
				Struct::ModelSubset subset;
				int numVerts, numTris, numWeights;

				fileIn >> checkString;					// Skip the "{"

				fileIn >> checkString;
				while (checkString != L"}")			// Read until '}'
				{
					// In this lesson, for the sake of simplicity, we will assume a textures filename is givin here.
					// Usually though, the name of a material (stored in a material library. Think back to the lesson on
					// loading .obj files, where the material library was contained in the file .mtl) is givin. Let this
					// be an exercise to load the material from a material library such as obj's .mtl file, instead of
					// just the texture like we will do here.
					if (checkString == L"shader")		// Load the texture or material
					{
						std::wstring fileNamePath;
						fileIn >> fileNamePath;			// Get texture's filename

						// Take spaces into account if filename or material name has a space in it
						if (fileNamePath[fileNamePath.size() - 1] != '"')
						{
							wchar_t checkChar;
							bool fileNameFound = false;
							while (!fileNameFound)
							{
								checkChar = fileIn.get();

								if (checkChar == '"')
									fileNameFound = true;

								fileNamePath += checkChar;
							}
						}

						// Remove the quotation marks from texture path
						fileNamePath.erase(0, 1);
						fileNamePath.erase(fileNamePath.size() - 1, 1);

						//check if this texture has already been loaded
						bool alreadyLoaded = false;
						for (int i = 0; i < texFileNameArray.size(); ++i)
						{
							if (fileNamePath == texFileNameArray[i])
							{
								alreadyLoaded = true;
								subset.texArrayIndex = i;
							}
						}

						//if the texture is not already loaded, load it now
						if (!alreadyLoaded)
						{
							ID3D11ShaderResourceView* tempMeshSRV;
							hr = D3DX11CreateShaderResourceViewFromFile(d3d11Device, fileNamePath.c_str(),
								NULL, NULL, &tempMeshSRV, NULL);
							if (SUCCEEDED(hr))
							{
								texFileNameArray.push_back(fileNamePath.c_str());
								subset.texArrayIndex = shaderResourceViewArray.size();
								shaderResourceViewArray.push_back(tempMeshSRV);
							}
							else
							{
								MessageBox(0, fileNamePath.c_str(),		//display message
									L"Could Not Open:", MB_OK);
	return false;
}
						}

						std::getline(fileIn, checkString);				// Skip rest of this line
					}
					else if (checkString == L"numverts")
					{
						fileIn >> numVerts;								// Store number of vertices

						std::getline(fileIn, checkString);				// Skip rest of this line

						for (int i = 0; i < numVerts; i++)
						{
							Vertex::Vertex tempVert;

							fileIn >> checkString						// Skip "vert # ("
								>> checkString
								>> checkString;

							fileIn >> tempVert.texCoord.x				// Store tex coords
								>> tempVert.texCoord.y;

							fileIn >> checkString;						// Skip ")"

							fileIn >> tempVert.StartWeight;				// Index of first weight this vert will be weighted to

							fileIn >> tempVert.WeightCount;				// Number of weights for this vertex

							std::getline(fileIn, checkString);			// Skip rest of this line

							subset.vertices.push_back(tempVert);		// Push back this vertex into subsets vertex vector
						}
					}
					else if (checkString == L"numtris")
					{
						fileIn >> numTris;
						subset.numTriangles = numTris;

						std::getline(fileIn, checkString);				// Skip rest of this line

						for (int i = 0; i < numTris; i++)				// Loop through each triangle
						{
							DWORD tempIndex;
							fileIn >> checkString;						// Skip "tri"
							fileIn >> checkString;						// Skip tri counter

							for (int k = 0; k < 3; k++)					// Store the 3 indices
							{
								fileIn >> tempIndex;
								subset.indices.push_back(tempIndex);
							}

							std::getline(fileIn, checkString);			// Skip rest of this line
						}
					}
					else if (checkString == L"numweights")
					{
						fileIn >> numWeights;

						std::getline(fileIn, checkString);				// Skip rest of this line

						for (int i = 0; i < numWeights; i++)
						{
							Struct::Weight tempWeight;
							fileIn >> checkString >> checkString;		// Skip "weight #"

							fileIn >> tempWeight.jointID;				// Store weight's joint ID

							fileIn >> tempWeight.bias;					// Store weight's influence over a vertex

							fileIn >> checkString;						// Skip "("

							fileIn >> tempWeight.pos.x					// Store weight's pos in joint's local space
								>> tempWeight.pos.z
								>> tempWeight.pos.y;

							std::getline(fileIn, checkString);			// Skip rest of this line

							subset.weights.push_back(tempWeight);		// Push back tempWeight into subsets Weight array
						}

					}
					else
						std::getline(fileIn, checkString);				// Skip anything else

					fileIn >> checkString;								// Skip "}"
				}

				//*** find each vertex's position using the joints and weights ***//
				for (int i = 0; i < subset.vertices.size(); ++i)
				{
					Vertex::Vertex tempVert = subset.vertices[i];
					tempVert.pos = XMFLOAT3(0, 0, 0);	// Make sure the vertex's pos is cleared first

					// Sum up the joints and weights information to get vertex's position
					for (int j = 0; j < tempVert.WeightCount; ++j)
					{
						Struct::Weight tempWeight = subset.weights[tempVert.StartWeight + j];
						Struct::Joint tempJoint = MD5Model.joints[tempWeight.jointID];

						// Convert joint orientation and weight pos to vectors for easier computation
						// When converting a 3d vector to a quaternion, you should put 0 for "w", and
						// When converting a quaternion to a 3d vector, you can just ignore the "w"
						XMVECTOR tempJointOrientation = XMVectorSet(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);
						XMVECTOR tempWeightPos = XMVectorSet(tempWeight.pos.x, tempWeight.pos.y, tempWeight.pos.z, 0.0f);

						// We will need to use the conjugate of the joint orientation quaternion
						// To get the conjugate of a quaternion, all you have to do is inverse the x, y, and z
						XMVECTOR tempJointOrientationConjugate = XMVectorSet(-tempJoint.orientation.x, -tempJoint.orientation.y, -tempJoint.orientation.z, tempJoint.orientation.w);

						// Calculate vertex position (in joint space, eg. rotate the point around (0,0,0)) for this weight using the joint orientation quaternion and its conjugate
						// We can rotate a point using a quaternion with the equation "rotatedPoint = quaternion * point * quaternionConjugate"
						XMFLOAT3 rotatedPoint;
						XMStoreFloat3(&rotatedPoint, XMQuaternionMultiply(XMQuaternionMultiply(tempJointOrientation, tempWeightPos), tempJointOrientationConjugate));

						// Now move the verices position from joint space (0,0,0) to the joints position in world space, taking the weights bias into account
						// The weight bias is used because multiple weights might have an effect on the vertices final position. Each weight is attached to one joint.
						tempVert.pos.x += (tempJoint.pos.x + rotatedPoint.x) * tempWeight.bias;
						tempVert.pos.y += (tempJoint.pos.y + rotatedPoint.y) * tempWeight.bias;
						tempVert.pos.z += (tempJoint.pos.z + rotatedPoint.z) * tempWeight.bias;

						// Basically what has happened above, is we have taken the weights position relative to the joints position
						// we then rotate the weights position (so that the weight is actually being rotated around (0, 0, 0) in world space) using
						// the quaternion describing the joints rotation. We have stored this rotated point in rotatedPoint, which we then add to
						// the joints position (because we rotated the weight's position around (0,0,0) in world space, and now need to translate it
						// so that it appears to have been rotated around the joints position). Finally we multiply the answer with the weights bias,
						// or how much control the weight has over the final vertices position. All weight's bias effecting a single vertex's position
						// must add up to 1.
					}

					subset.positions.push_back(tempVert.pos);			// Store the vertices position in the position vector instead of straight into the vertex vector
					// since we can use the positions vector for certain things like collision detection or picking
					// without having to work with the entire vertex structure.
				}

				// Put the positions into the vertices for this subset
				for (int i = 0; i < subset.vertices.size(); i++)
				{
					subset.vertices[i].pos = subset.positions[i];
				}

				//*** Calculate vertex normals using normal averaging ***///
				std::vector<XMFLOAT3> tempNormal;

				//normalized and unnormalized normals
				XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

				//Used to get vectors (sides) from the position of the verts
				float vecX, vecY, vecZ;

				//Two edges of our triangle
				XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
				XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

				//Compute face normals
				for (int i = 0; i < subset.numTriangles; ++i)
				{
					//Get the vector describing one edge of our triangle (edge 0,2)
					vecX = subset.vertices[subset.indices[(i * 3)]].pos.x - subset.vertices[subset.indices[(i * 3) + 2]].pos.x;
					vecY = subset.vertices[subset.indices[(i * 3)]].pos.y - subset.vertices[subset.indices[(i * 3) + 2]].pos.y;
					vecZ = subset.vertices[subset.indices[(i * 3)]].pos.z - subset.vertices[subset.indices[(i * 3) + 2]].pos.z;
					edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);	//Create our first edge

					//Get the vector describing another edge of our triangle (edge 2,1)
					vecX = subset.vertices[subset.indices[(i * 3) + 2]].pos.x - subset.vertices[subset.indices[(i * 3) + 1]].pos.x;
					vecY = subset.vertices[subset.indices[(i * 3) + 2]].pos.y - subset.vertices[subset.indices[(i * 3) + 1]].pos.y;
					vecZ = subset.vertices[subset.indices[(i * 3) + 2]].pos.z - subset.vertices[subset.indices[(i * 3) + 1]].pos.z;
					edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);	//Create our second edge

					//Cross multiply the two edge vectors to get the un-normalized face normal
					XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));

					tempNormal.push_back(unnormalized);
				}

				//Compute vertex normals (normal Averaging)
				XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
				int facesUsing = 0;
				float tX, tY, tZ;	//temp axis variables

				//Go through each vertex
				for (int i = 0; i < subset.vertices.size(); ++i)
				{
					//Check which triangles use this vertex
					for (int j = 0; j < subset.numTriangles; ++j)
					{
						if (subset.indices[j * 3] == i ||
							subset.indices[(j * 3) + 1] == i ||
							subset.indices[(j * 3) + 2] == i)
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

					//Store the normal and tangent in our current vertex
					subset.vertices[i].normal.x = -XMVectorGetX(normalSum);
					subset.vertices[i].normal.y = -XMVectorGetY(normalSum);
					subset.vertices[i].normal.z = -XMVectorGetZ(normalSum);

					///////////////**************new**************////////////////////
					// Create the joint space normal for easy normal calculations in animation
					Vertex::Vertex tempVert = subset.vertices[i];						// Get the current vertex
					subset.jointSpaceNormals.push_back(XMFLOAT3(0, 0, 0));		// Push back a blank normal
					XMVECTOR normal = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);		// Clear normal

					for (int k = 0; k < tempVert.WeightCount; k++)				// Loop through each of the vertices weights
					{
						Struct::Joint tempJoint = MD5Model.joints[subset.weights[tempVert.StartWeight + k].jointID];	// Get the joints orientation
						XMVECTOR jointOrientation = XMVectorSet(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);

						// Calculate normal based off joints orientation (turn into joint space)
						normal = XMQuaternionMultiply(XMQuaternionMultiply(XMQuaternionInverse(jointOrientation), normalSum), jointOrientation);

						XMStoreFloat3(&subset.weights[tempVert.StartWeight + k].normal, XMVector3Normalize(normal));			// Store the normalized quaternion into our weights normal
					}
					///////////////**************new**************////////////////////

					//Clear normalSum, facesUsing for next vertex
					normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
					facesUsing = 0;
				}

				// Create index buffer
				D3D11_BUFFER_DESC indexBufferDesc;
				ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

				indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				indexBufferDesc.ByteWidth = sizeof(DWORD) * subset.numTriangles * 3;
				indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				indexBufferDesc.CPUAccessFlags = 0;
				indexBufferDesc.MiscFlags = 0;

				D3D11_SUBRESOURCE_DATA iinitData;

				iinitData.pSysMem = &subset.indices[0];
				d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &subset.indexBuff);

				//Create Vertex Buffer
				D3D11_BUFFER_DESC vertexBufferDesc;
				ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

				vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;							// We will be updating this buffer, so we must set as dynamic
				vertexBufferDesc.ByteWidth = sizeof(Vertex::Vertex) * subset.vertices.size();
				vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;				// Give CPU power to write to buffer
				vertexBufferDesc.MiscFlags = 0;

				D3D11_SUBRESOURCE_DATA vertexBufferData;

				ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
				vertexBufferData.pSysMem = &subset.vertices[0];
				hr = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &subset.vertBuff);

				// Push back the temp subset into the models subset vector
				MD5Model.subsets.push_back(subset);
			}
		}
	}
	else
	{
		SwapChain->SetFullscreenState(false, NULL);	// Make sure we are out of fullscreen

		// create message
		std::wstring message = L"Could not open: ";
		message += filename;

		MessageBox(0, message.c_str(),	// display message
			L"Error", MB_OK);

		return false;
	}

	return true;
}
///////////////**************new**************////////////////////

///////////////**************new**************////////////////////
bool SeniorPro::LoadMD5Anim(std::wstring filename, Struct::Model3D& MD5Model)
{
	Struct::ModelAnimation tempAnim;						// Temp animation to later store in our model's animation array

	std::wifstream fileIn(filename.c_str());		// Open file

	std::wstring checkString;						// Stores the next string from our file

	if (fileIn)										// Check if the file was opened
	{
		while (fileIn)								// Loop until the end of the file is reached
		{
			fileIn >> checkString;					// Get next string from file

			if (checkString == L"MD5Version")		// Get MD5 version (this function supports version 10)
			{
				fileIn >> checkString;
				/*MessageBox(0, checkString.c_str(),	//display message
				L"MD5Version", MB_OK);*/
			}
			else if (checkString == L"commandline")
			{
				std::getline(fileIn, checkString);	// Ignore the rest of this line
			}
			else if (checkString == L"numFrames")
			{
				fileIn >> tempAnim.numFrames;				// Store number of frames in this animation
			}
			else if (checkString == L"numJoints")
			{
				fileIn >> tempAnim.numJoints;				// Store number of joints (must match .md5mesh)
			}
			else if (checkString == L"frameRate")
			{
				fileIn >> tempAnim.frameRate;				// Store animation's frame rate (frames per second)
			}
			else if (checkString == L"numAnimatedComponents")
			{
				fileIn >> tempAnim.numAnimatedComponents;	// Number of components in each frame section
			}
			else if (checkString == L"hierarchy")
			{
				fileIn >> checkString;				// Skip opening bracket "{"

				for (int i = 0; i < tempAnim.numJoints; i++)	// Load in each joint
				{
					Struct::AnimJointInfo tempJoint;

					fileIn >> tempJoint.name;		// Get joints name
					// Sometimes the names might contain spaces. If that is the case, we need to continue
					// to read the name until we get to the closing " (quotation marks)
					if (tempJoint.name[tempJoint.name.size() - 1] != '"')
					{
						wchar_t checkChar;
						bool jointNameFound = false;
						while (!jointNameFound)
						{
							checkChar = fileIn.get();

							if (checkChar == '"')
								jointNameFound = true;

							tempJoint.name += checkChar;
						}
					}

					// Remove the quotation marks from joints name
					tempJoint.name.erase(0, 1);
					tempJoint.name.erase(tempJoint.name.size() - 1, 1);

					fileIn >> tempJoint.parentID;			// Get joints parent ID
					fileIn >> tempJoint.flags;				// Get flags
					fileIn >> tempJoint.startIndex;			// Get joints start index

					// Make sure the joint exists in the model, and the parent ID's match up
					// because the bind pose (md5mesh) joint hierarchy and the animations (md5anim)
					// joint hierarchy must match up
					bool jointMatchFound = false;
					for (int k = 0; k < MD5Model.numJoints; k++)
					{
						if (MD5Model.joints[k].name == tempJoint.name)
						{
							if (MD5Model.joints[k].parentID == tempJoint.parentID)
							{
								jointMatchFound = true;
								tempAnim.jointInfo.push_back(tempJoint);
							}
						}
					}
					if (!jointMatchFound)					// If the skeleton system does not match up, return false
						return false;						// You might want to add an error message here

					std::getline(fileIn, checkString);		// Skip rest of this line
				}
			}
			else if (checkString == L"bounds")			// Load in the AABB for each animation
			{
				fileIn >> checkString;						// Skip opening bracket "{"

				for (int i = 0; i < tempAnim.numFrames; i++)
				{
					Struct::BoundingBox tempBB;

					fileIn >> checkString;					// Skip "("
					fileIn >> tempBB.min.x >> tempBB.min.z >> tempBB.min.y;
					fileIn >> checkString >> checkString;	// Skip ") ("
					fileIn >> tempBB.max.x >> tempBB.max.z >> tempBB.max.y;
					fileIn >> checkString;					// Skip ")"

					tempAnim.frameBounds.push_back(tempBB);
				}
			}
			else if (checkString == L"baseframe")			// This is the default position for the animation
			{												// All frames will build their skeletons off this
				fileIn >> checkString;						// Skip opening bracket "{"

				for (int i = 0; i < tempAnim.numJoints; i++)
				{
					Struct::Joint tempBFJ;

					fileIn >> checkString;						// Skip "("
					fileIn >> tempBFJ.pos.x >> tempBFJ.pos.z >> tempBFJ.pos.y;
					fileIn >> checkString >> checkString;		// Skip ") ("
					fileIn >> tempBFJ.orientation.x >> tempBFJ.orientation.z >> tempBFJ.orientation.y;
					fileIn >> checkString;						// Skip ")"

					tempAnim.baseFrameJoints.push_back(tempBFJ);
				}
			}
			else if (checkString == L"frame")		// Load in each frames skeleton (the parts of each joint that changed from the base frame)
			{
				Struct::FrameData tempFrame;

				fileIn >> tempFrame.frameID;		// Get the frame ID

				fileIn >> checkString;				// Skip opening bracket "{"

				for (int i = 0; i < tempAnim.numAnimatedComponents; i++)
				{
					float tempData;
					fileIn >> tempData;				// Get the data

					tempFrame.frameData.push_back(tempData);
				}

				tempAnim.frameData.push_back(tempFrame);

				///*** build the frame skeleton ***///
				std::vector<Struct::Joint> tempSkeleton;

				for (int i = 0; i < tempAnim.jointInfo.size(); i++)
				{
					int k = 0;						// Keep track of position in frameData array

					// Start the frames joint with the base frame's joint
					Struct::Joint tempFrameJoint = tempAnim.baseFrameJoints[i];

					tempFrameJoint.parentID = tempAnim.jointInfo[i].parentID;

					// Notice how I have been flipping y and z. this is because some modeling programs such as
					// 3ds max (which is what I use) use a right handed coordinate system. Because of this, we
					// need to flip the y and z axes. If your having problems loading some models, it's possible
					// the model was created in a left hand coordinate system. in that case, just reflip all the
					// y and z axes in our md5 mesh and anim loader.
					if (tempAnim.jointInfo[i].flags & 1)		// pos.x	( 000001 )
						tempFrameJoint.pos.x = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];

					if (tempAnim.jointInfo[i].flags & 2)		// pos.y	( 000010 )
						tempFrameJoint.pos.z = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];

					if (tempAnim.jointInfo[i].flags & 4)		// pos.z	( 000100 )
						tempFrameJoint.pos.y = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];

					if (tempAnim.jointInfo[i].flags & 8)		// orientation.x	( 001000 )
						tempFrameJoint.orientation.x = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];

					if (tempAnim.jointInfo[i].flags & 16)	// orientation.y	( 010000 )
						tempFrameJoint.orientation.z = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];

					if (tempAnim.jointInfo[i].flags & 32)	// orientation.z	( 100000 )
						tempFrameJoint.orientation.y = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];


					// Compute the quaternions w
					float t = 1.0f - (tempFrameJoint.orientation.x * tempFrameJoint.orientation.x)
						- (tempFrameJoint.orientation.y * tempFrameJoint.orientation.y)
						- (tempFrameJoint.orientation.z * tempFrameJoint.orientation.z);
					if (t < 0.0f)
					{
						tempFrameJoint.orientation.w = 0.0f;
					}
					else
					{
						tempFrameJoint.orientation.w = -sqrtf(t);
					}

					// Now, if the upper arm of your skeleton moves, you need to also move the lower part of your arm, and then the hands, and then finally the fingers (possibly weapon or tool too)
					// This is where joint hierarchy comes in. We start at the top of the hierarchy, and move down to each joints child, rotating and translating them based on their parents rotation
					// and translation. We can assume that by the time we get to the child, the parent has already been rotated and transformed based of it's parent. We can assume this because
					// the child should never come before the parent in the files we loaded in.
					if (tempFrameJoint.parentID >= 0)
					{
						Struct::Joint parentJoint = tempSkeleton[tempFrameJoint.parentID];

						// Turn the XMFLOAT3 and 4's into vectors for easier computation
						XMVECTOR parentJointOrientation = XMVectorSet(parentJoint.orientation.x, parentJoint.orientation.y, parentJoint.orientation.z, parentJoint.orientation.w);
						XMVECTOR tempJointPos = XMVectorSet(tempFrameJoint.pos.x, tempFrameJoint.pos.y, tempFrameJoint.pos.z, 0.0f);
						XMVECTOR parentOrientationConjugate = XMVectorSet(-parentJoint.orientation.x, -parentJoint.orientation.y, -parentJoint.orientation.z, parentJoint.orientation.w);

						// Calculate current joints position relative to its parents position
						XMFLOAT3 rotatedPos;
						XMStoreFloat3(&rotatedPos, XMQuaternionMultiply(XMQuaternionMultiply(parentJointOrientation, tempJointPos), parentOrientationConjugate));

						// Translate the joint to model space by adding the parent joint's pos to it
						tempFrameJoint.pos.x = rotatedPos.x + parentJoint.pos.x;
						tempFrameJoint.pos.y = rotatedPos.y + parentJoint.pos.y;
						tempFrameJoint.pos.z = rotatedPos.z + parentJoint.pos.z;

						// Currently the joint is oriented in its parent joints space, we now need to orient it in
						// model space by multiplying the two orientations together (parentOrientation * childOrientation) <- In that order
						XMVECTOR tempJointOrient = XMVectorSet(tempFrameJoint.orientation.x, tempFrameJoint.orientation.y, tempFrameJoint.orientation.z, tempFrameJoint.orientation.w);
						tempJointOrient = XMQuaternionMultiply(parentJointOrientation, tempJointOrient);

						// Normalize the orienation quaternion
						tempJointOrient = XMQuaternionNormalize(tempJointOrient);

						XMStoreFloat4(&tempFrameJoint.orientation, tempJointOrient);
					}

					// Store the joint into our temporary frame skeleton
					tempSkeleton.push_back(tempFrameJoint);
				}

				// Push back our newly created frame skeleton into the animation's frameSkeleton array
				tempAnim.frameSkeleton.push_back(tempSkeleton);

				fileIn >> checkString;				// Skip closing bracket "}"
			}
		}

		// Calculate and store some usefull animation data
		tempAnim.frameTime = 1.0f / tempAnim.frameRate;						// Set the time per frame
		tempAnim.totalAnimTime = tempAnim.numFrames * tempAnim.frameTime;	// Set the total time the animation takes
		tempAnim.currAnimTime = 0.0f;										// Set the current time to zero

		MD5Model.animations.push_back(tempAnim);							// Push back the animation into our model object
	}
	else	// If the file was not loaded
	{
		SwapChain->SetFullscreenState(false, NULL);	// Make sure we are out of fullscreen

		// create message
		std::wstring message = L"Could not open: ";
		message += filename;

		MessageBox(0, message.c_str(),				// display message
			L"Error", MB_OK);

		return false;
	}
	return true;
}

void SeniorPro::UpdateMD5Model(Struct::Model3D& MD5Model, float deltaTime, int animation)
{
	MD5Model.animations[animation].currAnimTime += deltaTime;			// Update the current animation time

	if (MD5Model.animations[animation].currAnimTime > MD5Model.animations[animation].totalAnimTime)
		MD5Model.animations[animation].currAnimTime = 0.0f;

	// Which frame are we on
	float currentFrame = MD5Model.animations[animation].currAnimTime * MD5Model.animations[animation].frameRate;
	int frame0 = floorf(currentFrame);
	int frame1 = frame0 + 1;

	// Make sure we don't go over the number of frames	
	if (frame0 == MD5Model.animations[animation].numFrames - 1)
		frame1 = 0;

	float interpolation = currentFrame - frame0;	// Get the remainder (in time) between frame0 and frame1 to use as interpolation factor

	std::vector<Struct::Joint> interpolatedSkeleton;		// Create a frame skeleton to store the interpolated skeletons in

	// Compute the interpolated skeleton
	for (int i = 0; i < MD5Model.animations[animation].numJoints; i++)
	{
		Struct::Joint tempJoint;
		Struct::Joint joint0 = MD5Model.animations[animation].frameSkeleton[frame0][i];		// Get the i'th joint of frame0's skeleton
		Struct::Joint joint1 = MD5Model.animations[animation].frameSkeleton[frame1][i];		// Get the i'th joint of frame1's skeleton

		tempJoint.parentID = joint0.parentID;											// Set the tempJoints parent id

		// Turn the two quaternions into XMVECTORs for easy computations
		XMVECTOR joint0Orient = XMVectorSet(joint0.orientation.x, joint0.orientation.y, joint0.orientation.z, joint0.orientation.w);
		XMVECTOR joint1Orient = XMVectorSet(joint1.orientation.x, joint1.orientation.y, joint1.orientation.z, joint1.orientation.w);

		// Interpolate positions
		tempJoint.pos.x = joint0.pos.x + (interpolation * (joint1.pos.x - joint0.pos.x));
		tempJoint.pos.y = joint0.pos.y + (interpolation * (joint1.pos.y - joint0.pos.y));
		tempJoint.pos.z = joint0.pos.z + (interpolation * (joint1.pos.z - joint0.pos.z));

		// Interpolate orientations using spherical interpolation (Slerp)
		XMStoreFloat4(&tempJoint.orientation, XMQuaternionSlerp(joint0Orient, joint1Orient, interpolation));

		interpolatedSkeleton.push_back(tempJoint);		// Push the joint back into our interpolated skeleton
	}

	for (int k = 0; k < MD5Model.numSubsets; k++)
	{
		for (int i = 0; i < MD5Model.subsets[k].vertices.size(); ++i)
		{
			Vertex::Vertex tempVert = MD5Model.subsets[k].vertices[i];
			tempVert.pos = XMFLOAT3(0, 0, 0);	// Make sure the vertex's pos is cleared first
			tempVert.normal = XMFLOAT3(0, 0, 0);	// Clear vertices normal

			// Sum up the joints and weights information to get vertex's position and normal
			for (int j = 0; j < tempVert.WeightCount; ++j)
			{
				Struct::Weight tempWeight = MD5Model.subsets[k].weights[tempVert.StartWeight + j];
				Struct::Joint tempJoint = interpolatedSkeleton[tempWeight.jointID];

				// Convert joint orientation and weight pos to vectors for easier computation
				XMVECTOR tempJointOrientation = XMVectorSet(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);
				XMVECTOR tempWeightPos = XMVectorSet(tempWeight.pos.x, tempWeight.pos.y, tempWeight.pos.z, 0.0f);

				// We will need to use the conjugate of the joint orientation quaternion
				XMVECTOR tempJointOrientationConjugate = XMQuaternionInverse(tempJointOrientation);

				// Calculate vertex position (in joint space, eg. rotate the point around (0,0,0)) for this weight using the joint orientation quaternion and its conjugate
				// We can rotate a point using a quaternion with the equation "rotatedPoint = quaternion * point * quaternionConjugate"
				XMFLOAT3 rotatedPoint;
				XMStoreFloat3(&rotatedPoint, XMQuaternionMultiply(XMQuaternionMultiply(tempJointOrientation, tempWeightPos), tempJointOrientationConjugate));

				// Now move the verices position from joint space (0,0,0) to the joints position in world space, taking the weights bias into account
				tempVert.pos.x += (tempJoint.pos.x + rotatedPoint.x) * tempWeight.bias;
				tempVert.pos.y += (tempJoint.pos.y + rotatedPoint.y) * tempWeight.bias;
				tempVert.pos.z += (tempJoint.pos.z + rotatedPoint.z) * tempWeight.bias;

				// Compute the normals for this frames skeleton using the weight normals from before
				// We can comput the normals the same way we compute the vertices position, only we don't have to translate them (just rotate)
				XMVECTOR tempWeightNormal = XMVectorSet(tempWeight.normal.x, tempWeight.normal.y, tempWeight.normal.z, 0.0f);

				// Rotate the normal
				XMStoreFloat3(&rotatedPoint, XMQuaternionMultiply(XMQuaternionMultiply(tempJointOrientation, tempWeightNormal), tempJointOrientationConjugate));

				// Add to vertices normal and ake weight bias into account
				tempVert.normal.x -= rotatedPoint.x * tempWeight.bias;
				tempVert.normal.y -= rotatedPoint.y * tempWeight.bias;
				tempVert.normal.z -= rotatedPoint.z * tempWeight.bias;
			}

			MD5Model.subsets[k].positions[i] = tempVert.pos;				// Store the vertices position in the position vector instead of straight into the vertex vector
			MD5Model.subsets[k].vertices[i].normal = tempVert.normal;		// Store the vertices normal
			XMStoreFloat3(&MD5Model.subsets[k].vertices[i].normal, XMVector3Normalize(XMLoadFloat3(&MD5Model.subsets[k].vertices[i].normal)));
		}

		// Put the positions into the vertices for this subset
		for (int i = 0; i < MD5Model.subsets[k].vertices.size(); i++)
		{
			MD5Model.subsets[k].vertices[i].pos = MD5Model.subsets[k].positions[i];
		}

		// Update the subsets vertex buffer
		// First lock the buffer
		D3D11_MAPPED_SUBRESOURCE mappedVertBuff;
		hr = d3d11DevCon->Map(MD5Model.subsets[k].vertBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedVertBuff);

		// Copy the data into the vertex buffer.
		memcpy(mappedVertBuff.pData, &MD5Model.subsets[k].vertices[0], (sizeof(Vertex::Vertex) * MD5Model.subsets[k].vertices.size()));

		d3d11DevCon->Unmap(MD5Model.subsets[k].vertBuff, 0);

		// The line below is another way to update a buffer. You will use this when you want to update a buffer less
		// than once per frame, since the GPU reads will be faster (the buffer was created as a DEFAULT buffer instead
		// of a DYNAMIC buffer), and the CPU writes will be slower. You can try both methods to find out which one is faster
		// for you. if you want to use the line below, you will have to create the buffer with D3D11_USAGE_DEFAULT instead
		// of D3D11_USAGE_DYNAMIC
		//d3d11DevCon->UpdateSubresource( MD5Model.subsets[k].vertBuff, 0, NULL, &MD5Model.subsets[k].vertices[0], 0, 0 );
	}
}
///////////////**************new**************////////////////////
