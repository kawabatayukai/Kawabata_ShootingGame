#pragma once
#include"BulletsBase.h"

// 狙ってくるやつ
class TakeAimBullets : public BulletsBase
{
public:
	//出現位置、プレイヤーの座標、スピード
	TakeAimBullets(T_LOCATION location, T_LOCATION p_location, float speed);

	void UpDate() override;           //更新
	void Draw() override;             //描画

	//生成座標と目標座標との角度を求める
	float GetRadian(T_LOCATION self, T_LOCATION target);

private:
	int image;    //画像
};

