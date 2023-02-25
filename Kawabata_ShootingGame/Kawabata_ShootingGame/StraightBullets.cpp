#include"DxLib.h"
#include "StraightBullets.h"

StraightBullets::StraightBullets(T_LOCATION location,T_LOCATION speed)
	:BulletsBase(location, 5.0f, 10, speed)    //上方向にまっすぐ
{
	//画像読み込み
	image = LoadGraph("images/bullets1.png");
}

//更新
void StraightBullets::UpDate()
{
	T_LOCATION newlocation = GetLocation();    //次の座標
	newlocation.y += speed.y;                  //座標を変更
	newlocation.x += speed.x;
	SetLocation(newlocation);                  //変更を反映
}

//描画
void StraightBullets::Draw()
{
	//DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(0, 200, 0));
	DrawRotaGraphF(GetLocation().x, GetLocation().y, 1, 0, image, TRUE);
}
