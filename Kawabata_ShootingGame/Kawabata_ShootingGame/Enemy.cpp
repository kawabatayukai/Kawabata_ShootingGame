#include"DxLib.h"
#include "Enemy.h"

//コンストラクタ
Enemy::Enemy(T_LOCATION location) : CharaBase(location, 20.0f, T_LOCATION{ 0,0.5 }), hp(10), point(10)
{

}

//更新
void Enemy::UpDate()
{
	//現在の位置
	T_LOCATION newLoacation = GetLocation();

	newLoacation.y += speed.y;
	SetLocation(newLoacation);
}

//描画
void Enemy::Draw()
{
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 255));
}

//当たった時の処理
void Enemy::Hit(int damage)
{
	//
	if (0 < damage)
	{
		hp -= damage;          //HP減少
		if (0 > hp) hp = 0;    //HPは0より下がらない
	}
}

//Hpチェック
bool Enemy::CheckHp()
{
	bool ret = (hp <= 0);
	return ret;
}