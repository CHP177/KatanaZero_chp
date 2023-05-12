#pragma once

class RenderTexture
{
public:
	void Initialize();

	void Update();

	void RenderToTexture();

	ComPtr<ID3D11ShaderResourceView> GetSRV() { return srv; }

private:
	ComPtr<ID3D11Texture2D> renderTargetTexture;
	ComPtr<ID3D11RenderTargetView> rtv;
	ComPtr<ID3D11ShaderResourceView> srv;

	Vector2 prevSize;
};
