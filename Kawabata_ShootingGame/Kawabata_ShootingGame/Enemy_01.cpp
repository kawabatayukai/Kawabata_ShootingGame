#include"DxLib.h"
#include"Enemy_01.h"
#include"TakeAimBullets.h"
#include"VortexBullets.h"

//コンストラクタ
Enemy_01::Enemy_01(T_LOCATION location, T_LOCATION speed)
	: Enemy_Base(location, 25.0f, speed, "CSV/moveinfo1.csv")
{
	//画像読み込み
	image = LoadGraph("images/ka.png");

	hp = 10;      //HPを設定
	point = 20;   //得点を設定

	//弾のスピードを設定
	SetBulletsSpeed(Bullet_Type::TakeAim, 7.0f);
	SetBulletsSpeed(Bullet_Type::Vortex, 6.0f);
	SetBulletsSpeed(Bullet_Type::Homing, 5.0f);
}


//描画
void Enemy_01::Draw()
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
		bool reverse = direction == Direction::RIGHT ? true : false;
		DrawRotaGraphF(GetLocation().x, GetLocation().y, 0.5, 0, image, TRUE, reverse);
	}
}