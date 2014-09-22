#ifndef D3DAPP_H
#define D3DAPP_H

// Includes
#include "d3dUtil.h"
#include <string>

// Class declaration
class D3DApp
{
	// Attributes
protected:
	HINSTANCE		mhAppInst;
	HWND			mhMainWnd;
	bool			mMinimized;
	bool			mMaximized;
	bool			mResizing;
	UINT			m4xMsaaQuality;
	std::wstring	mMainWndCaption;
	int				mClientWidth;
	int				mClientHeight;
	bool			mEnable4xMsaa;

	D3D_DRIVER_TYPE			md3dDriverType;
	ID3D11Device*			md3dDevice;
	ID3D11DeviceContext*	md3dImmediateContext;
	IDXGISwapChain*			mSwapChain;
	ID3D11Texture2D*		mDepthStencilBuffer;
	ID3D11RenderTargetView*	mRenderTargetView;
	ID3D11DepthStencilView*	mDepthStencilView;
	D3D11_VIEWPORT			mScreenViewport;

	// Methods
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();
	int Run();
	bool InitMainWindow();
	bool InitDirect3D();
	virtual bool Init();
	virtual void OnResize();
	virtual void UpdateScene(float dt) = 0;
	virtual void DrawScene() = 0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Getter methods
	HINSTANCE	AppInst() const;
	HWND		MainWnd() const;
	float		AspectRatio() const;

};

#endif  // D3DAPP_H
