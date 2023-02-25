#include"DxLib.h"
#include"Enemy_00.h"

//コンストラクタ
Enemy_00::Enemy_00(T_LOCATION location, T_LOCATION speed)
	: Enemy_Base(location, 20.0f, speed, "CSV/moveinfo.csv")
{
	//画像読み込み
	image = LoadGraph("images/goki.png");
	
	hp = 10;      //HPを設定
	point = 10;   //得点を設定
}

//描画
void Enemy_00::Draw()
{
	//弾
	for (int bulletCount = 0; bulletCount < BULLETS_MAX; bulletCount++)
	{
		//配列の空要素
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}

	//画像がないとき
	if (image == 0)
	{
		DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 255));
	}
	else
	{
		//元画像の0.5倍

		//向きによって反転/反転しない
		bool reverse = direction == Direction::LEFT ? true : false;
		DrawRotaGraphF(GetLocation().x, GetLocation().y, 0.7, 0, image, TRUE, reverse);
	}
}