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

int next[3] = { 1,2,1 }; //目標座標の添字
int frame_count = 0;     //フレームをカウント

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

	InputCSV();
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

	
	//パターン化された動き     0 : 動く/ 1 : 動かない 
	switch (moveinfo[current].pattern)
	{
	case 0:   //動く
		Move();
		break;

	case 1:   //動いていない

		frame_count++;                         //フレームをカウント

		//パターンで決められた待ち時間が経過
		if (moveinfo[current].waitTime <= frame_count)
		{
			frame_count = 0;                   //カウントをリセット
			current = moveinfo[current].next;  //次のパターンへ
		}

		break;

	default:
		break;
	}

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

	//attackpattern が0出ないとき攻撃する
	if (moveinfo[current].attackpattern != 0)
	{
		//配列の空要素  弾を発射する
		if (bulletCount < BULLETS_MAX && bullets[bulletCount] == nullptr)
		{
			if (moveinfo[current].attackpattern == 1)          //パターン1
			{
				//まっすぐ奴を生成
				bullets[bulletCount]
					= new StraightBullets(GetLocation(), T_LOCATION{ 0.0f,8.0f});
			}
			else if (moveinfo[current].attackpattern == 2)     //パターン2
			{
				//　　回転奴を生成
				bullets[bulletCount] = new VortexBullets(GetLocation(), 8.0f, (20 * shotNum));
				shotNum++;    //カウンターを増やす
			}
		}
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

	DrawFormatString(0, 50, 0xffffff, "No. : %d", current);
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
	////現在の位置
	//T_LOCATION nextLoacation = GetLocation();

	//speed = { 5.0f,5.0f };

	////目的座標と完全一致
	//if ((nextLoacation.y == locations[current].y) && (nextLoacation.x == locations[current].x))
	//{
	//	current = next[current];
	//}
	//else
	//{
	//	//ｙ座標が不一致
	//	if (nextLoacation.y != locations[current].y)
	//	{
	//		//目標座標のほうが大きい（目標は下）
	//		if (nextLoacation.y < locations[current].y)
	//		{
	//			nextLoacation.y += speed.y;  //下方向

	//			if ((GetLocation().y <= locations[current].y) && (locations[current].y <= nextLoacation.y))
	//			{
	//				nextLoacation.y = locations[current].y;  //到達後、目標を超えた場合停止
	//			}
	//		}
	//		else
	//		{
	//			nextLoacation.y -= speed.y;  //上方向
	//			if ((nextLoacation.y <= locations[current].y) && (locations[current].y <= GetLocation().y))
	//			{
	//				nextLoacation.y = locations[current].y;  //到達後、目標を超えた場合停止
	//			}
	//		}
	//	}

	//	//ｘ座標が不一致
	//	if (nextLoacation.x != locations[current].x)
	//	{
	//		//目標座標のほうが大きい（目標は右）
	//		if (nextLoacation.x < locations[current].x)
	//		{
	//			nextLoacation.x += speed.x;  //右方向
	//			if ((GetLocation().x <= locations[current].x) && (locations[current].x <= nextLoacation.x))
	//			{
	//				nextLoacation.x = locations[current].x;  //到達後、目標を超えた場合停止
	//			}
	//		}
	//		else
	//		{
	//			nextLoacation.x -= speed.x;
	//			if ((nextLoacation.x <= locations[current].x) && (locations[current].x <= GetLocation().x))
	//			{
	//				nextLoacation.x = locations[current].x;  //到達後、目標を超えた場合停止
	//			}
	//		}
	//	}
	//}



		//現在の位置
	T_LOCATION nextLoacation = GetLocation();

	speed = { 5.0f,5.0f };

	//目的座標と完全一致
	if ((nextLoacation.y == moveinfo[current].targetLocation.y) && (nextLoacation.x == moveinfo[current].targetLocation.x))
	{
		current = moveinfo[current].next;   //完全一致で次のパターンへ
	}
	else
	{
		//ｙ座標が不一致
		if (nextLoacation.y != moveinfo[current].targetLocation.y)
		{
			//目標座標のほうが大きい（目標は下）
			if (nextLoacation.y < moveinfo[current].targetLocation.y)
			{
				nextLoacation.y += speed.y;  //下方向

				if ((GetLocation().y <= moveinfo[current].targetLocation.y) && (moveinfo[current].targetLocation.y <= nextLoacation.y))
				{
					nextLoacation.y = moveinfo[current].targetLocation.y;  //到達後、目標を超えた場合停止
				}
			}
			else
			{
				nextLoacation.y -= speed.y;  //上方向
				if ((nextLoacation.y <= moveinfo[current].targetLocation.y) && (moveinfo[current].targetLocation.y <= GetLocation().y))
				{
					nextLoacation.y = moveinfo[current].targetLocation.y;  //到達後、目標を超えた場合停止
				}
			}
		}

		//ｘ座標が不一致
		if (nextLoacation.x != moveinfo[current].targetLocation.x)
		{
			//目標座標のほうが大きい（目標は右）
			if (nextLoacation.x < moveinfo[current].targetLocation.x)
			{
				nextLoacation.x += speed.x;  //右方向
				if ((GetLocation().x <= moveinfo[current].targetLocation.x) && (moveinfo[current].targetLocation.x <= nextLoacation.x))
				{
					nextLoacation.x = moveinfo[current].targetLocation.x;  //到達後、目標を超えた場合停止
				}
			}
			else
			{
				nextLoacation.x -= speed.x;
				if ((nextLoacation.x <= moveinfo[current].targetLocation.x) && (moveinfo[current].targetLocation.x <= GetLocation().x))
				{
					nextLoacation.x = moveinfo[current].targetLocation.x;  //到達後、目標を超えた場合停止
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

//csvファイル読み込み
void Enemy::InputCSV()
{
	FILE* fp; /*FILE型構造体*/
	errno_t error; /*fopen_sのエラー確認*/
	error = fopen_s(&fp, "CSV/moveinfo.csv", "r");

	/*(ブレイクポイントを付けて)ファイルの開閉テスト*/
	if (error != 0)
	{
		return; //エラー発生
	}
	else //ファイルを開いた
	{
		char line[100]; //行
		/*fgets(line, 文字数, fp)*/
		//fgets(line, 100, fp);
		//
		for (int i = 0; fgets(line, 100, fp) != NULL; i++)
		{


			sscanf_s(
				line, //行
				"%d,%f,%f,%d,%d,%d",       //(int, float, float, int, int, int)
				&moveinfo[i].pattern,          /*方法・パターン*/
				&moveinfo[i].targetLocation.x, /*目的地.X座標*/
				&moveinfo[i].targetLocation.y, /*目的地.Y座標*/
				&moveinfo[i].next,             /*次の(配列)処理*/
				&moveinfo[i].waitTime,    /*(待ちなど)時間*/
				&moveinfo[i].attackpattern     /*攻撃方法*/
			);

			
		}
		return;
	}
	fclose(fp); /*ファイルを閉じる*/
}