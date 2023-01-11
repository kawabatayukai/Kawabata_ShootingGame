#include"DxLib.h"
#include "Enemy.h"
#include"StraightBullets.h"
#include"VortexBullets.h"

#define BULLETS_MAX 100

//移動目標
T_LOCATION target[4] =
{
	{640,-10},
	{640,150},
	{100,150},
	{1180,150}
};

//移動目標座標
T_LOCATION locations[3] =
{
	{640,150},
	{1200.4f,150},
	{80.2f,150},
};

//移動情報　敵の動き
struct MoveInfo
{
	T_LOCATION targetLocation;   //目標
	int pattern;                 //動く/動かない
	int next;                    //
	int waitTime;                //
	int attackpattern;           //攻撃/攻撃しない  0:攻撃しない　0<n:攻撃
};

//10パターン
MoveInfo moveinfo[10] =
{
	{    640,150, 0, 1,  0, 0},
	{1200.4f,150, 0, 2,  0, 0},
	{      0,  0, 1, 3,180, 1},   //動かない 3秒間 攻撃
	{  80.2f,150, 0, 4,  0, 2},   //動く　　　　　 攻撃
	{      0,  0, 1, 5,180, 1},   //動かない 3秒間 攻撃
	{1200.4f,150, 0, 2,  0, 1},   
};

int next[3] = { 1,2,1 }; //目標座標の添字
int current = 0;         //現在〇番目の座標

//コンストラクタ
Enemy::Enemy(T_LOCATION location)
	: CharaBase(location, 20.0f, T_LOCATION{ 0,0.0 }), hp(10), point(10), shotNum(0),nowlocation(0)
{
	//メモリを確保する Bullets** bullets 
	bullets = new BulletsBase * [BULLETS_MAX];    //最大数　30  

	for (int i = 0; i < BULLETS_MAX; i++)
	{
		bullets[i] = nullptr;
	}
}

//更新
void Enemy::UpDate()
{
	////現在の位置
	//T_LOCATION newLoacation = GetLocation();

	//speed = { 3.0f,3.0f };
	//if (nowlocation < 2) speed = { 2.0f,2.0f };

	////順に移動する
	//if (target[nowlocation].x != newLoacation.x) speed.y = 0.0f;

	//if (target[nowlocation].x > newLoacation.x) speed.x = speed.x;
	//else if (target[nowlocation].x < newLoacation.x) speed.x = -speed.x;
	//else
	//{
	//	speed.x = 0.0f;

	//	if (target[nowlocation].y > newLoacation.y) speed.y = speed.y;
	//	else if (target[nowlocation].y < newLoacation.y) speed.y = -speed.y;
	//	else
	//	{
	//		speed.y = 0.0f;
	//		nowlocation++;

	//		if (nowlocation > 3) nowlocation = 2;
	//	}
	//}

	Move();

	//newLoacation.x += speed.x;
	//newLoacation.y += speed.y;
	//SetLocation(newLoacation);         //移動

	//弾 
	int bulletCount;
	for (bulletCount = 0; bulletCount < BULLETS_MAX; bulletCount++)
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
	if (bulletCount < BULLETS_MAX && bullets[bulletCount] == nullptr)
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
	for (int bulletCount = 0; bulletCount < BULLETS_MAX; bulletCount++)
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

//一定の移動
void Enemy::Move()
{
	//現在の位置
	T_LOCATION nextLoacation = GetLocation();

	speed = { 3.0f,3.0f };

	//目的座標と完全一致
	if ((nextLoacation.y == locations[current].y) && (nextLoacation.x == locations[current].x))
	{
		current = next[current];
	}
	else
	{
		//ｙ座標が不一致
		if (nextLoacation.y != locations[current].y)
		{
			//目標座標のほうが大きい（目標は下）
			if (nextLoacation.y < locations[current].y)
			{
				nextLoacation.y += speed.y;  //下方向

				if ((GetLocation().y <= locations[current].y) && (locations[current].y <= nextLoacation.y))
				{
					nextLoacation.y = locations[current].y;  //到達後、目標を超えた場合停止
				}
			}
			else
			{
				nextLoacation.y -= speed.y;  //上方向
				if ((nextLoacation.y <= locations[current].y) && (locations[current].y <= GetLocation().y))
				{
					nextLoacation.y = locations[current].y;  //到達後、目標を超えた場合停止
				}
			}
		}

		//ｘ座標が不一致
		if (nextLoacation.x != locations[current].x)
		{
			//目標座標のほうが大きい（目標は右）
			if (nextLoacation.x < locations[current].x)
			{
				nextLoacation.x += speed.x;  //右方向
				if ((GetLocation().x <= locations[current].x) && (locations[current].x <= nextLoacation.x))
				{
					nextLoacation.x = locations[current].x;  //到達後、目標を超えた場合停止
				}
			}
			else
			{
				nextLoacation.x -= speed.x;
				if ((nextLoacation.x <= locations[current].x) && (locations[current].x <= GetLocation().x))
				{
					nextLoacation.x = locations[current].x;  //到達後、目標を超えた場合停止
				}
			}
		}
	}

	SetLocation(nextLoacation);
}

//Hpチェック
bool Enemy::CheckHp()
{
	bool ret = (hp <= 0);
	return ret;
}