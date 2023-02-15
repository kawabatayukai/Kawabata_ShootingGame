#pragma once
#include "BulletsBase.h"

//渦
class VortexBullets : public BulletsBase
{
public:
	//出現位置のみ外部　半径・ダメージ・スピードは内部で設定
	VortexBullets(T_LOCATION location, float speed, int angle, unsigned int color = GetColor(0, 200, 0));

	virtual void UpDate() override;           //更新
	virtual void Draw() override;             //描画
	//virtual bool IsScreenOut() override;    //画面外/内

private:

	unsigned int color;   //色
};

