#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
	EnumerateAdapters();
	CreateSwapChain();
}

Graphics::~Graphics() {}

void Graphics::Begin()
{
	SetViewport();
	SetBackBufferToRTV();
}

void Graphics::End()
{
	HRESULT hr = swapChain->Present(bVsync, 0);
	CHECK(hr);
}

void Graphics::Resize(float width, float height)
{
	DeleteSurface();
	{
		HRESULT hr = swapChain->ResizeBuffers(0, (UINT)width, (UINT)height, DXGI_FORMAT_UNKNOWN, 0);
		CHECK(hr);
	}
	CreateRenderTargetView();
	SetViewport(width, height);
}

void Graphics::SetViewport(float width, float height)
{
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f; //default
	viewport.MaxDepth = 1.0f; //default
}

void Graphics::SetViewport()
{
	deviceContext->RSSetViewports(1, &viewport);
}

void Graphics::SetBackBufferToRTV()
{
	deviceContext->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);
	deviceContext->ClearRenderTargetView(rtv.Get(), clearColor);
}

void Graphics::EnumerateAdapters()
{
	ComPtr<IDXGIFactory1> factory;

	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory);
	CHECK(hr);

	UINT index = 0;
	while (true)
	{
		ComPtr<IDXGIAdapter1> adapter;
		HRESULT hr = factory->EnumAdapters1(index, &adapter);

		if (hr == DXGI_ERROR_NOT_FOUND)
			break;

		CHECK(hr);

		auto adapterInfo = make_shared<D3DEnumAdapterInfo>();
		adapterInfo->adapterOrdinal = index;
		adapter->GetDesc1(&adapterInfo->adapterDesc);
		adapterInfo->adapter = adapter;

		EnumerateAdapterOutput(adapterInfo);
		adapterInfos.push_back(adapterInfo);

		++index;
	}
}

bool Graphics::EnumerateAdapterOutput(const shared_ptr<D3DEnumAdapterInfo>& adapterInfo)
{
	//Output Base
	ComPtr<IDXGIOutput> outputBase;

	HRESULT hr = adapterInfo->adapter->EnumOutputs(0, &outputBase);

	if (hr == DXGI_ERROR_NOT_FOUND)
		return false;

	//Output
	ComPtr<IDXGIOutput1> output;

	outputBase->QueryInterface<IDXGIOutput1>(&output);

	auto outputInfo = make_shared<D3DEnumOutputInfo>();

	hr = output->GetDesc(&outputInfo->outputDesc);
	CHECK(hr);

	outputInfo->output = output;

	//Display Mode List
	UINT numModes = 0;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

	hr = output->GetDisplayModeList1(format, 0, &numModes, nullptr);

	vector<DXGI_MODE_DESC1> displayModes(numModes);

	hr = output->GetDisplayModeList1(format, 0, &numModes, displayModes.data());
	CHECK(hr);

	for (UINT i = 0; i < numModes; ++i)
	{
		resolutionList.push_back((Vector3((float)displayModes[i].Width, (float)displayModes[i].Height, (float)displayModes[i].RefreshRate.Numerator / (float)displayModes[i].RefreshRate.Denominator)));
		if (displayModes[i].Width == WIN_DEFAULT_WIDTH && displayModes[i].Height == WIN_DEFAULT_HEIGHT)
		{
			outputInfo->numerator = displayModes[i].RefreshRate.Numerator;
			outputInfo->denominator = displayModes[i].RefreshRate.Denominator;
		}
	}

	adapterInfo->outputInfo = outputInfo;

	return true;
}

void Graphics::CreateSwapChain()
{
	//SwapChain Description
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;

	//Main GPU Memory
	UINT maxVideoMemory = 0;

	for (UINT i = 0; i < adapterInfos.size(); ++i)
	{
		if (adapterInfos[i]->adapterDesc.DedicatedVideoMemory < maxVideoMemory)
		{
			selectedAdapterIndex = i;
			maxVideoMemory = (UINT)adapterInfos[i]->adapterDesc.DedicatedVideoMemory;
		}
	}

	const auto& adapterInfo = adapterInfos[selectedAdapterIndex];

	numerator = adapterInfo->outputInfo->numerator;
	denominator = adapterInfo->outputInfo->denominator;

	if (bVsync) //Maximum Refreshrate
	{
		desc.BufferDesc.RefreshRate.Numerator = numerator;
		desc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else //Unlimited
	{
		desc.BufferDesc.RefreshRate.Numerator = 0;
		desc.BufferDesc.RefreshRate.Denominator = 1;
	}

	gpuMemorySize = (UINT)adapterInfo->adapterDesc.DedicatedVideoMemory / 1024 / 1024; //GB
	gpuDescription = adapterInfo->adapterDesc.Description;

	cout << "DedicatedVideoMemory : " << gpuMemorySize << '\n';
	wcout << "GPU Description : " << gpuDescription << '\n';

	cout << "Numerator : " << numerator << '\n';
	cout << "Denominator : " << denominator << '\n';
	cout << "RefreshRate : " << numerator / denominator << "\n\n";

	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;						//Color Format
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	//Default
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					//Default
	desc.BufferCount = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.OutputWindow = gHandle;
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	vector<D3D_FEATURE_LEVEL> featureLevel { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };

	//Device And Swapchain
	HRESULT hr = D3D11CreateDeviceAndSwapChain
		(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevel.data(), (UINT)featureLevel.size(),
		D3D11_SDK_VERSION, &desc, &swapChain, &device, nullptr, &deviceContext);

	CHECK(hr);
	
	Resize(gWinWidth, gWinHeight);
}

void Graphics::CreateRenderTargetView()
{
	//BackBuffer
	ComPtr<ID3D11Texture2D> backBuffer;

	HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	CHECK(hr);

	//Render Target View
	hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, &rtv);
	CHECK(hr);
}

void Graphics::DeleteSurface()
{
	rtv.Reset();
}
