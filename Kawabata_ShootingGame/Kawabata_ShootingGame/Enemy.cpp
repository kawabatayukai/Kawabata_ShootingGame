#include"DxLib.h"
#include "Enemy.h"
#include"StraightBullets.h"
#include"VortexBullets.h"

//コンストラクタ
Enemy::Enemy(T_LOCATION location) : CharaBase(location, 20.0f, T_LOCATION{ 0,0.0 }), hp(10), point(10), shotNum(0)
{
	//メモリを確保する Bullets** bullets 
	bullets = new BulletsBase * [30];    //最大数　30  

	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}
}

//更新
void Enemy::UpDate()
{
	//現在の位置
	T_LOCATION newLoacation = GetLocation();
	newLoacation.y += speed.y;
	SetLocation(newLoacation);         //移動

	//弾 
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
			//if (shotNum > 0) shotNum--;

			bulletCount--;
		}
	}

	//配列の空要素
	if (bulletCount < 30 && bullets[bulletCount] == nullptr)
	{
		bullets[bulletCount] = new VortexBullets(GetLocation(), 3.0f, (20 * shotNum));
		shotNum++;
	}
}

//描画
void Enemy::Draw()
{
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 255));
	
	//弾
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