#include "d3dApp.h"
#include "CameraMain.h"
#include "VertexMain.h"
#include "Cubemap.h"
#include "Mesh.h"


#define MESHCOUNT 3

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
	void drawModel(bool transparent);

private:
	CameraMain mCam;

	Cubemap* mCubemap;

	//Mesh* spaceCompound;

	//meshArray[0] = Mesh(L"spaceCompound.obj");
	Mesh meshArray[MESHCOUNT];

	XMMATRIX groundWorld;
	XMMATRIX sphereWorld;

	XMMATRIX Rotation;
	XMMATRIX Scale;
	XMMATRIX Translation;
	float rot = 0.01f;

	UINT stride = sizeof(Vertex::Vertex);
	UINT offset = 0;

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
};

bool SeniorPro::InitScene()
{
	InitD2DScreenTexture();

	// Create cubemap
	mCubemap = new Cubemap(d3d11Device);
	//spaceCompound = new Mesh(L"spaceCompound.obj");
	//meshArray[0] = Mesh(L"spaceCompound.obj");

	///////////////**************new**************////////////////////
	if (!meshArray[0].LoadObjModel(L"Enemy.obj", material, true, false, d3d11Device, SwapChain))
		return false;
	if (!meshArray[1].LoadObjModel(L"spaceCompound.obj", material, true, false, d3d11Device, SwapChain))
		return false;
	if (!meshArray[2].LoadObjModel(L"ground.obj", material, true, true, d3d11Device, SwapChain))
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

	light.pos = XMFLOAT3(0.0f, 1.0f, 0.0f);
	light.dir = XMFLOAT3(0.0f, 0.0f, 1.0f);
	light.range = 1000.0f;
	light.cone = 20.0f;
	light.att = XMFLOAT3(0.4f, 0.02f, 0.000f);
	light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);


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

	///////////////**************new**************////////////////////
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
	///////////////**************new**************////////////////////

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

	return true;
}

void SeniorPro::UpdateScene(double time)
{
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

	///////////////**************new**************////////////////////
	// Will change to a forloop for every mesh in the mesh array
	for (int i = 0; i < MESHCOUNT; i++)
	{
		if (i == 0)
		{
			meshArray[i].meshWorld = XMMatrixIdentity();

			//Define cube1's world space matrix
			Rotation = XMMatrixRotationY(3.14f);
			Scale = XMMatrixScaling(0.25f, 0.25f, 0.25f);
			Translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}
		if (i == 1)
		{
			meshArray[i].meshWorld = XMMatrixIdentity();

			//Define cube1's world space matrix
			Rotation = XMMatrixRotationY(3.14f);
			Scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
			Translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}
		if (i == 2)
		{
			meshArray[i].meshWorld = XMMatrixIdentity();

			//Define cube1's world space matrix
			Rotation = XMMatrixRotationY(3.14f);
			Scale = XMMatrixScaling(10.0f, 1.0f, 10.0f);
			Translation = XMMatrixTranslation(0.0f, -0.02f, 0.0f);

			meshArray[i].meshWorld = Rotation * Scale * Translation;
		}
	}
	///////////////**************new**************////////////////////

	///////////////**************new**************////////////////////
	/*/ Will change to a forloop for every mesh in the mesh array
	meshArray[0].meshWorld = XMMatrixIdentity();

	//Define cube1's world space matrix
	Rotation = XMMatrixRotationY(3.14f);
	Scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	Translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	meshArray[0].meshWorld = Rotation * Scale * Translation;
	///////////////**************new**************////////////////////

	light.pos.x = XMVectorGetX(mCam.getCamPosition());
	light.pos.y = XMVectorGetY(mCam.getCamPosition());
	light.pos.z = XMVectorGetZ(mCam.getCamPosition());

	light.dir.x = XMVectorGetX(mCam.getCamTarget()) - light.pos.x;
	light.dir.y = XMVectorGetY(mCam.getCamTarget()) - light.pos.y;
	light.dir.z = XMVectorGetZ(mCam.getCamTarget()) - light.pos.z;
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
			<< L"Lives: " << Player1.getLives() << "\n";
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
	//Draw our model's NON-transparent subsets
	drawModel(false);
	///////////////**************new**************////////////////////

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

	///////////////**************new**************////////////////////	
	//Draw our model's TRANSPARENT subsets now
	drawModel(true);
	///////////////**************new**************////////////////////	

	RenderText(L"Health: ", Player1.getHealth());
	RenderText(L"Lives: ", Player1.getLives());
	RenderText(L"Health: ", PlayerWep.getMagSize());

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
	if (keyboardState[DIK_A] & 0x80)
	{
		//moveLeftRight -= speed;
		mCam.setMoveLeftRight(mCam.getMoveLeftRight() - speed);
	}
	if (keyboardState[DIK_D] & 0x80)
	{
		//moveLeftRight += speed;
		mCam.setMoveLeftRight(mCam.getMoveLeftRight() + speed);
	}
	if (keyboardState[DIK_W] & 0x80)
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
		thePlayer.setDeath(false);
	}

	if ((mouseCurrState.rgbButtons[0]))
	{
		if (PlayerWep.getMagSize() <= 0){
			reloadBro = true;
		}
		else if (flip == false){
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
			flip = true;
		}
	}
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

void SeniorPro::drawModel(bool transparent)
{
	if (transparent)
	{
		///////////////**************new**************////////////////////	
		//Draw our model's TRANSPARENT subsets now

		//Set our blend state

		d3d11DevCon->OMSetBlendState(Transparency, NULL, 0xffffffff);

		for (int j = 0; j < MESHCOUNT; j++){

			for (int i = 0; i < meshArray[j].subsetCount; ++i)
			{
				//Set the grounds index buffer
				d3d11DevCon->IASetIndexBuffer(meshArray[j].indexBuff, DXGI_FORMAT_R32_UINT, 0);
				//Set the grounds vertex buffer
				d3d11DevCon->IASetVertexBuffers(0, 1, &meshArray[j].vertBuff, &stride, &offset);

				//Set the WVP matrix and send it to the constant buffer in effect file
				mCam.setWVP(meshArray[j].meshWorld, mCam.getCamView(), mCam.getCamProjection());
				cbPerObj.WVP = XMMatrixTranspose(mCam.getWVP());
				cbPerObj.World = XMMatrixTranspose(meshArray[j].meshWorld);
				cbPerObj.difColor = material[meshArray[j].subsetTexture[i]].difColor;
				cbPerObj.hasTexture = material[meshArray[j].subsetTexture[i]].hasTexture;
				d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
				d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
				d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerObjectBuffer);
				if (material[meshArray[j].subsetTexture[i]].hasTexture)
					d3d11DevCon->PSSetShaderResources(0, 1, &meshArray[j].meshSRV[material[meshArray[j].subsetTexture[i]].texArrayIndex]);
				d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

				d3d11DevCon->RSSetState(RSCullNone);
				int indexStart = meshArray[j].subsetIndexStart[i];
				int indexDrawAmount = meshArray[j].subsetIndexStart[i + 1] - meshArray[j].subsetIndexStart[i];
				if (material[meshArray[j].subsetTexture[i]].transparent)
					d3d11DevCon->DrawIndexed(indexDrawAmount, indexStart, 0);
			}
		}
		///////////////**************new**************////////////////////	
	}
	else
	{
		///////////////**************new**************////////////////////
		//Draw our model's NON-transparent subsets
		for (int j = 0; j < MESHCOUNT; j++){
			for (int i = 0; i < meshArray[j].subsetCount; ++i)
			{
				//Set the grounds index buffer
				d3d11DevCon->IASetIndexBuffer(meshArray[j].indexBuff, DXGI_FORMAT_R32_UINT, 0);
				//Set the grounds vertex buffer
				d3d11DevCon->IASetVertexBuffers(0, 1, &meshArray[j].vertBuff, &stride, &offset);

				//Set the WVP matrix and send it to the constant buffer in effect file
				mCam.setWVP(meshArray[j].meshWorld, mCam.getCamView(), mCam.getCamProjection());
				cbPerObj.WVP = XMMatrixTranspose(mCam.getWVP());
				cbPerObj.World = XMMatrixTranspose(meshArray[j].meshWorld);
				cbPerObj.difColor = material[meshArray[j].subsetTexture[i]].difColor;
				cbPerObj.hasTexture = material[meshArray[j].subsetTexture[i]].hasTexture;
				d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
				d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
				d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerObjectBuffer);
				if (material[meshArray[j].subsetTexture[i]].hasTexture)
					d3d11DevCon->PSSetShaderResources(0, 1, &meshArray[j].meshSRV[material[meshArray[j].subsetTexture[i]].texArrayIndex]);
				d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

				d3d11DevCon->RSSetState(RSCullNone);
				int indexStart = meshArray[j].subsetIndexStart[i];
				int indexDrawAmount = meshArray[j].subsetIndexStart[i + 1] - meshArray[j].subsetIndexStart[i];
				if (!material[meshArray[j].subsetTexture[i]].transparent)
					d3d11DevCon->DrawIndexed(indexDrawAmount, indexStart, 0);
			}
		}
		///////////////**************new**************////////////////////
	}
}

