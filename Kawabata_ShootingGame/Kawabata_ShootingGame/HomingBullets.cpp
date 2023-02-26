#include"HomingBullets.h"
#include"DxLib.h"

#define _USE_MATH_DEFINES
#include<math.h>

#define HOMING_TIME 100        //追跡時間

//コンストラクタ
HomingBullets::HomingBullets(T_LOCATION location, float speed)
	:BulletsBase(location, 6.0f, 5, T_LOCATION{ speed,speed })
{
	angle = M_PI / 2;   //初期の角度

	//画像読み込み
	image = LoadGraph("images/bullets2.png");
}

//更新
void HomingBullets::Update()
{
	//現在の座標
	T_LOCATION nowlocation = GetLocation();

	//追跡時間内　　　時間外で諦める
	if (time_counter < HOMING_TIME)
	{
		//現在進んでいる方向
		double now_x = cos(angle);    //ｘ軸
		double now_y = sin(angle);    //ｙ軸

		//本来進むべき方向
		double nxt_x = static_cast<double>(target.x) - nowlocation.x;    //ｘ軸
		double nxt_y = static_cast<double>(target.y) - nowlocation.y;    //ｙ軸



		double radius = 8;            //移動半径

		//外積を利用し向きをターゲット側に向ける
		if (((nxt_x * now_y) - (nxt_y * now_x)) < 0.0)
		{
			angle += M_PI / 180 * radius;
		}
		else
		{
			angle -= M_PI / 180 * radius;
		}

		time_counter++;                                   //追跡時間カウント
	}

	nowlocation.x += static_cast<float>(cos(angle)) * speed.x;      //cos(角度)　でｘ軸の移動量を計算
	nowlocation.y += static_cast<float>(sin(angle)) * speed.y;      //sin(角度)　でｙ軸の移動量を計算

	//座標をセット
	SetLocation(nowlocation);
}

//描画
void HomingBullets::Draw() 
{
	DrawRotaGraphF(GetLocation().x, GetLocation().y, 1, 0, image, TRUE);
}