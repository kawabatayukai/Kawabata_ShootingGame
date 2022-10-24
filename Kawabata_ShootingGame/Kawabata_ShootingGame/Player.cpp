#include"DxLib.h"
#include "Player.h"
#include"StraightBullets.h"

//コンストラクタ          初期位置      　　　　　　   radius        speed               
Player::Player(T_LOCATION location) : CharaBase(location, 10.0f, T_LOCATION{ 2,2 }), score(0), life(10)
{
	//メモリを確保する Bullets** bullets 
	
	bullets = new BulletsBase * [30];    //最大数　30  

	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}
}

//更新
void Player::UpDate()
{
	//現在の位置
	T_LOCATION newLoacation = GetLocation();

	newLoacation.x += 1;
	SetLocation(newLoacation);


	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//配列の空要素
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->UpDate();
	}


	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//配列の空要素
		if (bulletCount < 30 && bullets[bulletCount] == nullptr)
		{
			bullets[bulletCount] = new StraightBullets(GetLocation());
		}

	}


}

//描画
void Player::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 0));


	for (int bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//配列の空要素
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
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
