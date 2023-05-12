#pragma once

class Drawable : public Object
{
public:
	Drawable(const string& name, const Vector2 position, const Vector2& scale, float rotation, const wstring& shaderPath = L"");
	Drawable(const Drawable& other) : Drawable(other.name, other.position, other.scale, other.rotation, other.shaderPath) {}
	Drawable operator=(const Drawable& other)
	{
		Drawable obj(other);
		return obj;
	}
	virtual ~Drawable() = default;

	void SetShader(const wstring& shaderPath);

public:
	void Update() override;
	void Render() override;
	
	void DrawCall(const D3D11_PRIMITIVE_TOPOLOGY& topology, bool indexed = true);

protected:
	unique_ptr<VertexBuffer> VB;
	unique_ptr<IndexBuffer> IB;
	unique_ptr<InputLayout> IL;
	unique_ptr<VertexShader> VS;
	unique_ptr<PixelShader> PS;

	wstring shaderPath = L"";

};
