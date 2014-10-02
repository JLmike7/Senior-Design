// Include base class declaration
#include "D3DApp.h"
#include "Camera.h"

// Subclass declaration
class D3DTestApp : public D3DApp
{
public:
	D3DTestApp(HINSTANCE);
	~D3DTestApp();

	// Overriden methods
	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);

private:
	void BuildDynamicCubeMapViews();

private:
	// Dynamic Cube Map
	ID3D11DepthStencilView* mDynamicCubeMapDSV;
	ID3D11RenderTargetView* mDynamicCubeMapRTV[6];
	ID3D11ShaderResourceView* mDynamicCubeMapSRV;
	D3D11_VIEWPORT mCubeMapViewport;

	static const int CubeMapSize = 256;

	// Camera 
	Camera mCam;
	Camera mCubeMapCamera[6];

	// Mouse Point
	POINT mLastMousePos;
};

// Class methods
D3DTestApp::D3DTestApp(HINSTANCE hInstance) : D3DApp(hInstance)
{
	// Caption
	mMainWndCaption = L"Senior Design Project";
	// Mouse Position
	mLastMousePos.x = 0;
	mLastMousePos.y = 0;
	// setting the camera position
	mCam.SetPosition(0.0f, 2.0f, -15.0f);
	// Setting the maps 
	for (int i = 0; i < 6; ++i)
	{
		mDynamicCubeMapRTV[i] = 0;
	}


};

D3DTestApp::~D3DTestApp(){
	ReleaseCOM(mDynamicCubeMapDSV);
	ReleaseCOM(mDynamicCubeMapSRV);
	for (int i = 0; i < 6; ++i)
		ReleaseCOM(mDynamicCubeMapRTV[i]);


};

bool D3DTestApp::Init()
{
	// Simply use base class initializer
	if (!D3DApp::Init())
	{
		return false;
	}

	return true;
}

void D3DTestApp::OnResize()
{
	// Simply use base class resize
	D3DApp::OnResize();
}

void D3DTestApp::UpdateScene(float dt)
{};

void D3DTestApp::DrawScene()
{
	// Check for valid rendering context and swap chain
	assert(md3dImmediateContext);
	assert(mSwapChain);

	// Simply clear render view to blue
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Blue));

	// Clear depth buffer to 1.0 and stenci buffer to 0
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Swap back buffer
	HR(mSwapChain->Present(0, 0));
};


// Windows main function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	// Add some debug flags if debugging
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Instantiate application object
	D3DTestApp theApp(hInstance);

	// Initialize the application
	if (!theApp.Init())
	{
		 return 0;
	}
	 
	// Execute the application
	return theApp.Run();
}


