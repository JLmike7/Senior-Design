// Include base class declaration
#include "D3DApp.h"

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
	void DrawScene(); //asdfads
};

// Class methods
D3DTestApp::D3DTestApp(HINSTANCE hInstance) : D3DApp(hInstance)
{};

D3DTestApp::~D3DTestApp()
{};

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


