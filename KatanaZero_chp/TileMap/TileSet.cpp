#include "stdafx.h"
#include "TileSet.h"

TileSet::TileSet(const wstring& texturePath, UINT spacing)
	: texturePath(texturePath), spacing(spacing)
{
	LoadFromWICFile(texturePath.c_str(), WIC_FLAGS_NONE, nullptr, tileSprite);

	HRESULT hr = CreateShaderResourceView(DEVICE.Get(), tileSprite.GetImages(), tileSprite.GetImageCount(), tileSprite.GetMetadata(), &srv);
	CHECK(hr);

	texID = srv.Get();
	imageSize = Vector2((float)tileSprite.GetMetadata().width, (float)tileSprite.GetMetadata().height);

	tileXCount = (UINT)tileSprite.GetMetadata().width / spacing;
	tileYCount = (UINT)tileSprite.GetMetadata().height / spacing;

	texelTileSize = Vector2(1 / (float)tileXCount, 1 / (float)tileYCount);
}

void TileSet::GUI()
{
	static bool bOpen = true;
	ImGui::Begin("TileSprite", &bOpen);
	{
		int index = 0;

		for (UINT y = 0; y < tileYCount; ++y)
		{
			for (UINT x = 0; x < tileXCount; ++x)
			{
				ImGui::PushID(++index);

				if (ImGui::ImageButton(texID, ImVec2(40, 40), ImVec2(x * texelTileSize.x, y * texelTileSize.y), ImVec2((x + 1) * texelTileSize.x, (y + 1) * texelTileSize.y)))
				{
					selectedStartUV = Vector2(x * texelTileSize.x, y * texelTileSize.y);
				}

				ImGui::PopID();

				if (index % 8 != 0)
					ImGui::SameLine();
			}
		}
	}

	ImGui::End();
}
