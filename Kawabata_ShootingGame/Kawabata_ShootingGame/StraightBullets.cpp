#include"DxLib.h"
#include "StraightBullets.h"

StraightBullets::StraightBullets(T_LOCATION location)
	:BulletsBase(location, 5.0f, 3, T_LOCATION{ 0,5 })    //上方向にまっすぐ
{

}

//更新
void StraightBullets::UpDate()
{
	T_LOCATION newlocation = GetLocation();    //次の座標
	newlocation.y -= speed.y;                  //座標を変更

	SetLocation(newlocation);                  //変更を反映
}

//描画
void StraightBullets::Draw()
{
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(0, 200, 0));
}

//画面外/内
bool StraightBullets::IsScreenOut()
{
	//StraightBulletsは上方向に直進のみ
	bool ret = ((GetLocation().y + GetRadius()) <= 0);

	return ret;
}