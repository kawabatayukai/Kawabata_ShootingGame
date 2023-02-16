#pragma once
#include"BulletsBase.h"

//バウンド
class BoundBullets : public BulletsBase
{
public:
	//コンストラクタ
	BoundBullets(T_LOCATION location, float speed);

	void UpDate() override;           //更新
	void Draw() override;             //描画

private:
	float angle;               //角度
};