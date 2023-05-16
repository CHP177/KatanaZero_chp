#include "stdafx.h"
#include "TileMap.h"
#include "TileSet.h"

TileMap::TileMap(const Vector2& position, const Vector2& scale, float rotation, const wstring& tileSetPath, UINT spacing)
	: Drawable("TileMap", position, scale, rotation, L"_Shaders/VertexTile.hlsl"), spacing(spacing)
{
	tileSet = make_unique<TileSet>(tileSetPath);

	width = (UINT)scale.x / spacing;
	height = (UINT)scale.y / spacing;

	GenerateTileMap(width, height, spacing);

	vertices.assign(4, VertexTexture());

	vertices[0].position = Vector2(0, 0);
	vertices[1].position = Vector2(0, (float)spacing);
	vertices[2].position = Vector2((float)spacing, 0);
	vertices[3].position = Vector2((float)spacing, (float)spacing);

	vertices[0].uv = Vector2(0, 1);
	vertices[1].uv = Vector2(0, 0);
	vertices[2].uv = Vector2(1, 1);
	vertices[3].uv = Vector2(1, 0);

	VB->Create(vertices, D3D11_USAGE_DYNAMIC);

	indices = { 0, 1, 2, 2, 1, 3 };
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexTexture::descs.data(), VertexTexture::descs.size(), VS->GetBlob());

	srv = tileSet->srv;
}

void TileMap::Update()
{
}

void TileMap::Render()
{
}

void TileMap::GUI()
{
}

void TileMap::GenerateTileMap(UINT width, UINT height, UINT spacing)
{
}

Tile* TileMap::GetTile(const Vector2& unProjectedMousePos)
{
    return nullptr;
}

void TileMap::SaveTileMap(const wstring& path)
{
}

void TileMap::LoadTileMap(const wstring& path)
{
}
