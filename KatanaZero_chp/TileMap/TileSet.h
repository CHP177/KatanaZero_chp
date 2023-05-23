#pragma once

class TileSet
{
public:
	friend class TileMap;

	TileSet(const wstring& texturePath, UINT spacing);
	~TileSet() = default;

	void GUI();

private:
	wstring texturePath;

	ScratchImage tileSprite;
	ComPtr<ID3D11ShaderResourceView> srv;

	ImTextureID texID;
	Vector2 imageSize;
	UINT spacing;
	UINT tileXCount = 0;
	UINT tileYCount = 0;
	Vector2 texelTileSize;

	Vector2 selectedStartUV;

};
