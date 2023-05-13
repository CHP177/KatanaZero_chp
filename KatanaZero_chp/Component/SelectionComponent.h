#pragma once

class SelectionComponent : public Component
{
public:
	SelectionComponent(UINT slot = 1, const bool* bOutline = false);

public:
	void Update() override;
	void Render() override;

public:
	void SetOutline(bool bOutline) { SB->SetOutline(bOutline); }

private:
	unique_ptr<SelectionBuffer> SB;
	UINT slot = 0;

};
