#include "stdafx.h"
#include "Object.h"

void Object::AddComponent(const shared_ptr<Component>& component)
{
	if (components.count(component->GetName()))
		return;

	components.emplace(component->GetName(), component);
	component->SetOwner(this);
}

void Object::DeleteComponent(const string& name)
{
	components.erase(name);
}

void Object::Update()
{
	S = XMMatrixScalingFromVector(scale);
	R = XMMatrixRotationZ(-rotation);
	T = XMMatrixTranslationFromVector(position);

	world = S * R * T;

	WB->SetWorld(world);
}

void Object::Render()
{
	WB->SetVSBuffer(0);
}
