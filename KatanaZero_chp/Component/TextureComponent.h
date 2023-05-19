#pragma once

class TextureComponent : public Component
{
public:
	TextureComponent(const wstring& texturePath = L"", UINT slot = 0, const string& name = "Texture", bool bMagenta = true);

public:
	wstring GetPath() const { return texturePath; }
	ScratchImage* GetImage() { return &image; }
	
	void SetSRV(const ComPtr<ID3D11ShaderResourceView>& srv) { this->srv = srv; }
	void SetSRV(const wstring& texturePath);

	void SetIsMagenta(bool bMagenta) { this->bMagenta = bMagenta; }

public:
	void Render() override;

private:
	ComPtr<ID3D11ShaderResourceView> srv;
	wstring texturePath = L"";

	ScratchImage image;

	UINT slot = 0;

	bool bMagenta = true;

	ComPtr<ID3D11BlendState> blendState;
	ComPtr<ID3D11SamplerState> samplerState;
};
