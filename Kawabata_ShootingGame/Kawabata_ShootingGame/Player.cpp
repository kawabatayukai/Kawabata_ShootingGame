#include"DxLib.h"
#include "Player.h"
#include"StraightBullets.h"
#include"KeyManager.h"

//コンストラクタ          初期位置      　　　　　　   radius        speed               
Player::Player(T_LOCATION location) : CharaBase(location, 10.0f, T_LOCATION{ 5,5 }), score(0), life(10)
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

	if (KeyManager::OnKeyPressed(KEY_INPUT_W)) newLoacation.y -= speed.y;
	if (KeyManager::OnKeyPressed(KEY_INPUT_S)) newLoacation.y += speed.y;
	if (KeyManager::OnKeyPressed(KEY_INPUT_A)) newLoacation.x -= speed.x;
	if (KeyManager::OnKeyPressed(KEY_INPUT_D)) newLoacation.x += speed.x;
	
	SetLocation(newLoacation);


	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//配列の空要素
		if (bullets[bulletCount] == nullptr) break;
		bullets[bulletCount]->UpDate();

		//画面外で削除する
		if (bullets[bulletCount]->IsScreenOut() == true)
		{
			DeleteBullet(bulletCount);   //弾を削除する
			bulletCount--;
		}
	}


	if (KeyManager::OnMousePressed(MOUSE_INPUT_LEFT))
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
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 0));


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
void Player::Hit(int damage)
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
