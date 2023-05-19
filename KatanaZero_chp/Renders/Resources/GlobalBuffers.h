#pragma once

#include "stdafx.h"

class WorldBuffer : public ConstantBuffer
{
public:
	struct WorldStruct
	{
		Matrix world;
	};

public:
	WorldBuffer() : ConstantBuffer(&data, sizeof(WorldStruct)) {}

	void SetWorld(const Matrix& world) { data.world = XMMatrixTranspose(world); }

private:
	WorldStruct data;
};

class ViewProjectionBuffer : public ConstantBuffer
{
public:
	struct ViewProjStruct
	{
		Matrix view;
		Matrix projection;
	};

public:
	ViewProjectionBuffer() : ConstantBuffer(&data, sizeof(ViewProjStruct)) {}

	void SetView(const Matrix& view) { data.view = XMMatrixTranspose(view); }
	void SetProjection(const Matrix& projection) { data.projection = XMMatrixTranspose(projection); }

private:
	ViewProjStruct data;

};

class ColorBuffer : public ConstantBuffer
{
public:
	struct ColorStruct
	{
		Color color;
	};

public:
	ColorBuffer() : ConstantBuffer(&data, sizeof(ColorStruct)) {}

	void SetColor(const Color& color) { data.color = color; }

private:
	ColorStruct data;

};

class SelectionBuffer : public ConstantBuffer
{
	struct SelectionStruct
	{
		UINT selection = 1;
		Vector2 textureSize = { gWinWidth, gWinHeight };
		bool bOutline = false;
	};

public:
	SelectionBuffer() : ConstantBuffer(&data, sizeof(SelectionStruct)) {}

	void SetSeletion(const UINT& selection) { data.selection = selection; }
	void SetTextureSize(const Vector2& size) { data.textureSize = size; }
	void SetOutline(const bool& bOutline) { data.bOutline = bOutline; }

private:
	SelectionStruct data;

};