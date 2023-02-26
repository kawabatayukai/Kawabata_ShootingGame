#pragma once
#include"BulletsBase.h"

//ホーミング
class HomingBullets : public BulletsBase
{
public:
	//コンストラクタ
	HomingBullets(T_LOCATION location, float speed);

	void Update() override;           //更新
	void Draw() override;             //描画

private:
	double angle;                     //角度
	int time_counter = 0;             //追跡時間をカウント

	int image;                        //画像
};