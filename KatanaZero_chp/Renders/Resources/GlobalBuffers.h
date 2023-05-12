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

	void SetWorld(const Matrix& world)
	{
		data.world = XMMatrixTranspose(world);
	}

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

	void SetView(const Matrix& view)
	{
		data.view = XMMatrixTranspose(view);
	}

	void SetProjection(const Matrix& projection)
	{
		data.projection = XMMatrixTranspose(projection);
	}

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
	ColorBuffer() : ConstantBuffer(&data, sizeof(ColorBuffer)) {}

	void SetColor(const Color& color)
	{
		data.color = color;
	}

private:
	ColorStruct data;

};