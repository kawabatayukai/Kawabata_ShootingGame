#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>

#include "VortexBullets.h"

VortexBullets::VortexBullets(T_LOCATION location, float speed, int angle, unsigned int color)
	: BulletsBase(location, 5.0f, 5, T_LOCATION{ 0,0 }), color(color)
{
	//speed.x = cosf(angle* 3.14f / 180);
	//speed.y = sinf(angle* 3.14f / 180);

	int deg = angle % 360;
	double rad = (M_PI / 180) * deg;   //角度１の実数値＊360度法

	//0除算(n/0)を回避
	float x = static_cast<float>((abs(deg) == 90 || abs(deg) == 270) ? 0 : cos(rad)); //横軸cos
	float y = static_cast<float>(sin(rad));                                           //縦軸sin

	//(sin+cos)=1   縦と横に進む比率 sin・cosで
	this->speed = T_LOCATION{ (speed * x),(speed * y) };
}

//更新
void VortexBullets::UpDate()
{
	T_LOCATION newlocation = GetLocation();    //次の座標


	newlocation.y += speed.y;                  //座標を変更
	newlocation.x += speed.x;
	SetLocation(newlocation);                  //変更を反映
}

//描画
void VortexBullets::Draw()
{
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), color);
}

////画面外/内
//bool VortexBullets::IsScreenOut()
//{
//	
//	//StraightBulletsは上方向に直進のみ
//	bool ret = ((GetLocation().y + GetRadius()) <= 0 || (GetLocation().y - GetRadius() >= 720)|| (GetLocation().x + GetRadius()) <= 0 || (GetLocation().x - GetRadius()) >= 1280);
//	return ret;
//
//	//ret = ((GetLocation().x + GetRadius()) <= 0 || (GetLocation().x - GetRadius()) >= 1280);
//	//return ret;
//}
