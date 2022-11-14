#pragma once
#include "ItemBase.h"
class Recovery : public ItemBase
{
public:
	Recovery(T_LOCATION location);

	virtual void UpDate() override;
	virtual void Draw() const override;
	int GetVolume() const { return volume; }       //‰ñ•œ—ÍŽæ“¾

private:
	int volume;     //‰ñ•œ—Ê
};

