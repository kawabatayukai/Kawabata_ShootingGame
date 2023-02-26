#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>

#include "VortexBullets.h"

VortexBullets::VortexBullets(T_LOCATION location, float speed, int angle, unsigned int color)
	: BulletsBase(location, 6.0f, 5, T_LOCATION{ 0,0 }), color(color)
{
	int deg = angle % 360;
	double rad = (M_PI / 180) * deg;   //角度１の実数値＊360度法

	//0除算(n/0)を回避
	float x = static_cast<float>((abs(deg) == 90 || abs(deg) == 270) ? 0 : cos(rad)); //横軸cos
	float y = static_cast<float>(sin(rad));                                           //縦軸sin

	//(sin+cos)=1   縦と横に進む比率 sin・cosで
	this->speed = T_LOCATION{ (speed * x),(speed * y) };

	//画像読み込み
	image = LoadGraph("images/bullets4.png");
}

//更新
void VortexBullets::Update()
{
	T_LOCATION newlocation = GetLocation();    //次の座標


	newlocation.y += speed.y;                  //座標を変更
	newlocation.x += speed.x;
	SetLocation(newlocation);                  //変更を反映
}

//描画
void VortexBullets::Draw()
{
	//DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), color);
	DrawRotaGraphF(GetLocation().x, GetLocation().y, 1, 0, image, TRUE);
}
