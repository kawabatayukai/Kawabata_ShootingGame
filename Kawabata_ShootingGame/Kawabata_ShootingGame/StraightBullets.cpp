#include"DxLib.h"
#include "StraightBullets.h"

StraightBullets::StraightBullets(T_LOCATION location)
	:BulletsBase(location, 5.0f, 3, T_LOCATION{ 0,9 })    //上方向にまっすぐ
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
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 0));
}