#pragma once
#include "Interaction.h"
class Shop_Blacksmith : public Interaction
{
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual void InteractionAction()override;
	Shop_Blacksmith(int x, int y);
	virtual ~Shop_Blacksmith() = default;
};

