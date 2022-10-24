#pragma once
#include "BulletsBase.h"

//ストレート
class StraightBullets : public BulletsBase
{
public:
	//出現位置のみ外部　半径・ダメージ・スピードは内部で設定
	StraightBullets(T_LOCATION location);

	virtual void UpDate() override;           //更新
	virtual void Draw() override;             //描画

private:

};

