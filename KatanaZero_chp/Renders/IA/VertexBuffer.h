#pragma once

struct Vertex
{
	Vertex() : Vertex(Vector2(), Vector2()) {}
	Vertex(const Vector2& position, const Vector2& uv)
		: position(position), uv(uv)
	{}

	Vector2 position;
	Vector2 uv;

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

vector<D3D11_INPUT_ELEMENT_DESC> Vertex::descs
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

class VertexBuffer
{
public:
	ID3D11Buffer* GetResource() const { return buffer.Get(); }
	UINT GetStride() const { return stride; }
	UINT GetOffset() const { return offset; }
	UINT GetCount() const { return count; }

public:
	void Create(const vector<Vertex>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);
	void SetIA();

private:
	ComPtr<ID3D11Buffer> buffer;
	UINT stride = 0;
	UINT offset = 0;
	UINT count = 0;
};