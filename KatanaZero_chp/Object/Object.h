#pragma once

class Object
{
public:
	Object(string name, const Vector2& position, const Vector2& scale, float rotation)
		: name(name), position(position), scale(scale), rotation(XMConvertToRadians(rotation))
	{
		WB = make_unique<WorldBuffer>();
	}
	Object(const Object& other) : Object(other.name, other.position, other.scale, other.rotation) {}
	Object operator=(const Object& other)
	{
		Object obj(other);
		return obj;
	}
	virtual ~Object() {}

public:
	void AddComponent(const shared_ptr<Component>& component);
	void DeleteComponent(const string& name);
	template<typename T>
	shared_ptr<T> GetComponent(const string& compName) const
	{
		if (!components.count(compName))
			return nullptr;

		return dynamic_pointer_cast<T>(components.at(compName));
	}

public:
	inline Vector2 GetPosition() const { return position; }
	inline Vector2 GetScale() const { return scale; }

	inline float GetTop() const { return position.y + scale.y / 2; }
	inline float GetBottom() const { return position.y - scale.y / 2; }
	inline float GetRight() const { return position.x + scale.x / 2; }
	inline float GetLeft() const { return position.x - scale.x / 2; }

	inline float GetRotation() const { return rotation; }
	inline float GetRotationDegree() const { return XMConvertToDegrees(rotation); }

	inline Vector2 GetRightVector() const { return Vector2((R * T)._11, (R * T)._12); }
	inline Vector2 GetUpVector() const { return Vector2((R * T)._21, (R * T)._22); }
	inline Matrix GetS() const { return S; }
	inline Matrix GetR() const { return R; }
	inline Matrix GetT() const { return T; }

	void SetPosition(Vector2 position) { this->position = position; }
	void SetTop() { this->position = Vector2(CENTER_X, gWinHeight - GetScale().y / 2.0f); }
	void SetBottom() { this->position = Vector2(CENTER_X, GetScale().y / 2.0f); }
	void SetScale(Vector2 scale) { this->scale = scale; }
	void SetRotation(float rotation) { this->rotation = XMConvertToRadians(rotation); }

	void SetWorld(const Matrix& world)
	{
		this->world = world;
		WB->SetWorld(world);
	}

	void Move(const Vector2& position) { this->position += position * TIME->GetDeltaTime(); }
	void Scale(const Vector2& scale) { this->scale += scale * TIME->GetDeltaTime(); }
	void Rotate(float rotation) { this->rotation += XMConvertToRadians(rotation) * TIME->GetDeltaTime(); }

public:
	virtual void Update();
	virtual void Render();

	virtual void GUI();

protected:
	string name;
	map<string, shared_ptr<Component>> components;

protected:
	unique_ptr<WorldBuffer> WB;
	Matrix world, S, R, T;

	Vector2 position, scale;
	float rotation = 0.0f;

	Color color;

};