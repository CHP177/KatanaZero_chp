#pragma once

struct D3DEnumAdapterInfo;
struct D3DEnumOutputInfo;

class Graphics
{
	DECLARE_SINGLETON(Graphics);

public:
	ComPtr<ID3D11Device> GetDevice() const { return device; }
	ComPtr<ID3D11DeviceContext> GetDC() const { return deviceContext; }

	void Begin();
	void End();

public:
	void Resize(float width, float height);
	void SetViewport(float width, float height);
	void SetViewport();
	void SetBackBufferToRTV();

	bool GetVSync() const { return bVsync; }
	void SetVSync(bool bVsync) { this->bVsync = bVsync; }

	Color GetClearColor() const { return clearColor; }

private:
	void EnumerateAdapters();
	bool EnumerateAdapterOutput(const shared_ptr<D3DEnumAdapterInfo>& adapterInfo);

private:
	void CreateSwapChain();
	void CreateRenderTargetView();
	void DeleteSurface();

private:
	//Graphics
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGISwapChain> swapChain;

	ComPtr<ID3D11RenderTargetView> rtv;
	D3D11_VIEWPORT viewport = { 0 };
	Color clearColor = { 0.4f, 0.4f, 0.4f, 1.0f };

	//refreshrator
	UINT numerator = 0;
	UINT denominator = 1;

	//GPU
	UINT gpuMemorySize = 0;
	wstring gpuDescription = L"";

	//Adapters
	vector<shared_ptr<D3DEnumAdapterInfo>> adapterInfos; //Vector that save infomation for Adapter
	int selectedAdapterIndex = 0;						 //Index of Main GPU

	bool bVsync = true;

	vector<Vector3> resolutionList;						 //Resolution list of Monitor
};

struct D3DEnumAdapterInfo
{
	UINT adapterOrdinal = 0;
	ComPtr<IDXGIAdapter1> adapter;
	DXGI_ADAPTER_DESC1 adapterDesc = { 0 };

	shared_ptr<D3DEnumOutputInfo> outputInfo;
};

struct D3DEnumOutputInfo
{
	ComPtr<IDXGIOutput1> output;
	DXGI_OUTPUT_DESC outputDesc = { 0 };

	UINT numerator = 0;
	UINT denominator = 1;
};