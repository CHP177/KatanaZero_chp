#pragma once

struct Tile
{
	Vector2 pos;
	Vector2 uvStart;
	Vector2 uvEnd;
};

class TileMap : public Drawable
{
public:
	TileMap(const Vector2& position, const Vector2& scale, float rotation, const wstring& tileSetPath = L"", UINT spacing = 40);
	~TileMap() = default;

	void SetSRV(const ComPtr<ID3D11ShaderResourceView>& srv) { this->srv = srv; }

	void Update() override;
	void Render() override;

	void GUI();
	void SaveTileMapToImageFile(const wstring& path = L"");

private:
	void GenerateTileMap(UINT width, UINT height, UINT spacing);
	Tile* GetTile(const Vector2& unProjectedMousePos);

	void SaveTileMap(const wstring& path = L"");
	void LoadTileMap(const wstring& path = L"");

private:
	UINT width = 0, height = 0;
	UINT spacing = 0;

	vector<VertexTexture> vertices;
	vector<UINT> indices;
	vector<vector<Tile>> tiles;

	ComPtr<ID3D11ShaderResourceView> srv;

	unique_ptr<class TileSet> tileSet;

};
