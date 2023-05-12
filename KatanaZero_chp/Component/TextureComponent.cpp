#include "stdafx.h"
#include "TextureComponent.h"

TextureComponent::TextureComponent(const wstring& texturePath, UINT slot, const string& name, bool bMagenta)
	: Component(name), texturePath(texturePath), slot(slot), bMagenta(bMagenta)
{
	if (texturePath != L"")
		SetSRV(texturePath);

	//CreateBlendState
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;

		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		HRESULT hr = DEVICE->CreateBlendState(&desc, &blendState);
		CHECK(hr);
	}

	//CreateSamplerState
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.MipLODBias = 0;
		desc.MaxAnisotropy = 16;
		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		desc.BorderColor[0] = 1.0f;
		desc.BorderColor[1] = 1.0f;
		desc.BorderColor[2] = 1.0f;
		desc.BorderColor[3] = 1.0f;
		desc.MinLOD = -FLT_MAX;
		desc.MaxLOD = FLT_MAX;

		HRESULT hr = DEVICE->CreateSamplerState(&desc, &samplerState);
		CHECK(hr);
	}
}

void TextureComponent::SetSRV(const wstring& texturePath)
{
	this->texturePath = texturePath;

	LoadFromWICFile(texturePath.c_str(), WIC_FLAGS_IGNORE_SRGB, nullptr, image);

	HRESULT hr = CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), &srv);
	CHECK(hr);
}

void TextureComponent::Render()
{
	DC->PSSetShaderResources(0, 1, srv.GetAddressOf());

	if (bMagenta)
		DC->PSSetSamplers(0, 1, samplerState.GetAddressOf());

	if (Path::GetExtension(texturePath) == L"png")
		DC->OMSetBlendState(blendState.Get(), nullptr, 0xffffffff);
}
