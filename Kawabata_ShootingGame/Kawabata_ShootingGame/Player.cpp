#include"DxLib.h"
#include "Player.h"

//コンストラクタ          初期位置      　　　　　　   radius        speed               
Player::Player(T_LOCATION location) : CharaBase(location, 10.0f, T_LOCATION{ 2,2 }), score(0), life(10)
{

}

//更新
void Player::UpDate()
{
	//現在の位置
	T_LOCATION newLoacation = GetLocation();

	newLoacation.x += 1;
	SetLocation(newLoacation);
}

//描画
void Player::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 0));
}

//当たった時の処理
void Player::Hit()
{

}

//"life"を確認
bool Player::LifeCheck()
{
	bool ret = (life <= 0);
	return ret;
}

//スコア取得
int Player::GetScore() const { return score; }
