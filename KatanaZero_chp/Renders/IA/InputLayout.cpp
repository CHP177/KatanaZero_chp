#include "stdafx.h"
#include "InputLayout.h"

void InputLayout::Create(const D3D11_INPUT_ELEMENT_DESC* desc, const size_t& count, const ComPtr<ID3DBlob>& blob)
{
	if (!desc || !count || !blob.Get())
		assert(false);

	HRESULT hr = DEVICE->CreateInputLayout(desc, (UINT)count, blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);
	CHECK(hr);
}

void InputLayout::SetIA()
{
	DC->IASetInputLayout(inputLayout.Get());
}
