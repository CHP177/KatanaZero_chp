#include "stdafx.h"
#include "SelectionComponent.h"

SelectionComponent::SelectionComponent(UINT slot, const bool* bOutline)
	: Component("Selection"), slot(slot)
{
	SB = make_unique<SelectionBuffer>();
	SetOutline(bOutline);
}

void SelectionComponent::Update()
{

}

void SelectionComponent::Render()
{
	SB->SetPSBuffer(slot);
}
