#include "TakeAimBullets.h"
#include"DxLib.h"
#include<math.h>

//出現位置、プレイヤーの座標、スピード
TakeAimBullets::TakeAimBullets(T_LOCATION location, T_LOCATION p_location, float speed)
	:BulletsBase(location, 5.0f, 3, T_LOCATION{0,0})
{
	//角度を決める
	float rad = GetRadian(location, p_location);

	//スピードを決める
	this->speed.x = cosf(rad) * speed;
	this->speed.y = sinf(rad) * speed;
}

//更新
void TakeAimBullets::UpDate()
{
	T_LOCATION newlocation = GetLocation();    //次の座標
	newlocation.y += speed.y;                  //座標を変更
	newlocation.x += speed.x;
	SetLocation(newlocation);                  //変更を反映
}

//描画
void TakeAimBullets::Draw()
{
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 200, 0));
}

//生成座標と目標座標との角度を求める
float TakeAimBullets::GetRadian(T_LOCATION self, T_LOCATION target)
{
	float w = target.x - self.x;     //ｘ座標の差分（cosθ）
	float h = target.y - self.y;     //ｙ座標の差分（sinθ）

	//逆正接の主値を求める(?)
	return atan2f(h, w);
}