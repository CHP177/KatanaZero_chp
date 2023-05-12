#pragma once

class LineRect : public Drawable
{
public:
	LineRect(const Vector2& position, const Vector2& scale, float rotation, const Color& color);
	LineRect(const LineRect& other) : LineRect(other.position, other.scale, other.rotation, other.color) {}
	LineRect operator=(const LineRect other)
	{
		LineRect obj(other);
		return obj;
	}

public:
	void Update() override;
	void Render() override;

private:
	vector<VertexColor> vertices;
	vector<UINT> indices;

	Color color;
};