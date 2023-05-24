#include "stdafx.h"
#include "TileMap.h"
#include "TileSet.h"

TileMap::TileMap(const Vector2& position, const Vector2& scale, float rotation, const wstring& tileSetPath, UINT spacing)
	: Drawable("TileMap", position, scale, rotation, L"_Shaders/VertexTile.hlsl"), spacing(spacing)
{
	tileSet = make_unique<TileSet>(tileSetPath, spacing);

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
	if (ImGui::IsAnyItemActive())
		return;

	SUPER::Update();

	if (INPUT->Press(VK_LBUTTON))
	{
		Vector2 mPos = CAMERA->UnProject(INPUT->GetMousePosition());
		Tile* tile = GetTile(mPos);

		if (tile)
		{
			tile->uvStart = tileSet->selectedStartUV;
			tile->uvEnd = tileSet->selectedStartUV + tileSet->texelTileSize;
		}
	}
}

void TileMap::Render()
{
	SUPER::Render();

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DC->PSSetShaderResources(0, 1, srv.GetAddressOf());

	for (UINT y = 0; y < height; ++y)
	{
		for (UINT x = 0; x < width; ++x)
		{
			const Tile& tile = tiles[y][x];

			D3D11_MAPPED_SUBRESOURCE subResource;

			DC->Map(VB->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
			{
				vertices[0].uv = Vector2(tile.uvStart.x, tile.uvEnd.y);
				vertices[1].uv = tile.uvStart;
				vertices[2].uv = tile.uvEnd;
				vertices[3].uv = Vector2(tile.uvEnd.x, tile.uvStart.y);

				memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
			}
			DC->Unmap(VB->GetResource(), 0);

			SetWorld(XMMatrixTranslationFromVector(tile.pos + position));
			WB->SetVSBuffer(0);

			DC->DrawIndexed(IB->GetCount(), 0, 0);
		}
	}
}

void TileMap::GUI()
{
	tileSet->GUI();

	static bool bOpen = true;
	if (ImGui::Begin("TileMap", &bOpen))
	{
		if (ImGui::Button("Save", ImVec2(50, 30)))
			SaveTileMap();

		if (ImGui::Button("Load", ImVec2(50, 30)))
			LoadTileMap();
	}
	ImGui::End();
}

void TileMap::GenerateTileMap(UINT width, UINT height, UINT spacing)
{
	if (width == 0 || height == 0 || spacing == 0)
	{
		assert(false);
		return;
	}
	tiles.clear();
	tiles.assign(height, vector<Tile>());
	for (UINT y = 0; y < height; ++y)
	{
		tiles[y].assign(width, Tile());

		for (UINT x = 0; x < width; ++x)
		{
			tiles[y][x].pos = Vector2((float)x, (float)y) * spacing;
		}
	}
}

Tile* TileMap::GetTile(const Vector2& unProjectedMousePos)
{
	UINT x = (UINT)unProjectedMousePos.x / spacing;
	UINT y = (UINT)unProjectedMousePos.y / spacing;

	if (x >= width || y >= height || x < 0 || y < 0)
		return nullptr;

	return &tiles[y][x];
}

void TileMap::SaveTileMap(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&TileMap::SaveTileMap, this, placeholders::_1);
		Path::SaveFileDialog(L"", Path::MapFilter, L"_Maps/", func, gHandle);
	}
	else
	{
		if (tiles.empty()) return;

		ofstream out(path.c_str());

		if (out.is_open())
		{
			out.write((char*)&width, sizeof(width));
			out.write((char*)&height, sizeof(height));
			out.write((char*)&spacing, sizeof(spacing));

			for (UINT i = 0; i < height; ++i)
				out.write((char*)tiles[i].data(), sizeof(tiles[0][0]) * tiles[i].size());
		}

		out.close();
	}
}

void TileMap::SaveTileMapToImageFile(const wstring& path)
{
	//Texture2D
	ID3D11Texture2D* texture;

	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	textureDesc.Width = scale.x;
	textureDesc.Height = scale.y;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	HRESULT hr = DEVICE->CreateTexture2D(&textureDesc, nullptr, &texture);
	CHECK(hr);
	
	//Render Target View
	ID3D11RenderTargetView* rtv;

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	ZeroMemory(&rtvDesc, sizeof(rtvDesc));

	rtvDesc.Format = textureDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	hr = DEVICE->CreateRenderTargetView(texture, &rtvDesc, &rtv);
	CHECK(hr);

	ScratchImage image;
	CaptureTexture(DEVICE.Get(), DC.Get(), texture, image);

	wstring ext = path.substr(path.find_last_of(L".") + 1);

	WICCodecs extCodec = WIC_CODEC_BMP;
	if (ext == L"jpg" && ext == L"jpeg")
		extCodec = WIC_CODEC_JPEG;
	else if (ext == L"png")
		extCodec = WIC_CODEC_PNG;
	else if (ext == L"GIF")
		extCodec = WIC_CODEC_GIF;

	SaveToWICFile(image.GetImages(), image.GetImageCount(), WIC_FLAGS_FORCE_SRGB, GetWICCodec(extCodec), path.c_str());
}

void TileMap::LoadTileMap(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&TileMap::LoadTileMap, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::MapFilter, L"_Maps/", func, gHandle);
	}
	else
	{
		ifstream in(path.c_str());

		if (in.is_open())
		{
			in.read((char*)&width, sizeof(width));
			in.read((char*)&height, sizeof(height));
			in.read((char*)&spacing, sizeof(spacing));

			GenerateTileMap(width, height, spacing);
			for (UINT i = 0; i < height; ++i)
				in.read((char*)tiles[i].data(), sizeof(tiles[0][0]) * tiles[i].size());
		}

		in.close();
	}
}
