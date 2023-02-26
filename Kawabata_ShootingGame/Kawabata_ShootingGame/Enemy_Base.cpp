#include"DxLib.h"
#include"Enemy_Base.h"
#include"StraightBullets.h"
#include"VortexBullets.h"
#include"TakeAimBullets.h"
#include"HomingBullets.h"

//コンストラクタ
Enemy_Base::Enemy_Base(T_LOCATION location, float radius, T_LOCATION speed, const char* pass)
	: CharaBase(location, radius, speed), moveinfo(), direction(Direction::LEFT)
{
	//Bullet * BULLETS_MAX分のメモリを確保
	bullets = new BulletsBase * [BULLETS_MAX];    //最大数　100  

	//初期化
	for (int i = 0; i < BULLETS_MAX; i++) bullets[i] = nullptr;


	//CSV読み込み
	if (pass != nullptr) InputCSV(pass);
}

//更新
void Enemy_Base::Update()
{

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

	//弾 
	int bulletCount;
	for (bulletCount = 0; bulletCount < BULLETS_MAX; bulletCount++)
	{
		//配列の空要素なら抜ける
		if (bullets[bulletCount] == nullptr) break;

		bullets[bulletCount]->Update();
		bullets[bulletCount]->SetTargetLocation(target);

		//画面外で削除する
		if (bullets[bulletCount]->IsScreenOut() == true)
		{
			DeleteBullet(bulletCount);   //弾を削除する

			bulletCount--;
		}
	}

	//attackpattern が0出ないとき攻撃する
	if (moveinfo[current].attackpattern != 0)
	{
		//配列の空要素  弾を発射する
		if (bulletCount < BULLETS_MAX && bullets[bulletCount] == nullptr && frame_count % 30 == 0)
		{
			if (moveinfo[current].attackpattern == 1)          //パターン1
			{
				//自機狙い
				bullets[bulletCount]
					= new TakeAimBullets(GetLocation(), target, speed_TakeAim);
				
			}
			else if (moveinfo[current].attackpattern == 2)     //パターン2
			{
				//回転弾を生成
				bullets[bulletCount] = 
					new VortexBullets(GetLocation(), speed_Vortex, (30 * shotNum));
				shotNum++;    //カウンターを増やす
			}
			else if (moveinfo[current].attackpattern == 3)     //パターン2
			{
				//ホーミング弾を生成
				bullets[bulletCount] = 
					new HomingBullets(GetLocation(), speed_Homing);
			}
		}
	}
}

//描画
void Enemy_Base::Draw()
{
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

	//画像がないとき
	if (image == 0)
	{
		DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 255));
	}
	else
	{
		//0.5倍
		DrawRotaGraphF(GetLocation().x, GetLocation().y, 0.5, 0, image, TRUE);
	}

}

//当たった時の処理
void Enemy_Base::Hit(int damage)
{
	//
	if (0 < damage)
	{
		hp -= damage;          //HP減少
		if (0 > hp) hp = 0;    //HPは0より下がらない
	}
}

//一定の移動
void Enemy_Base::Move()
{
    //現在の位置
	T_LOCATION nextLoacation = GetLocation();

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
				direction = Direction::RIGHT;

				if ((GetLocation().x <= moveinfo[current].targetLocation.x) && (moveinfo[current].targetLocation.x <= nextLoacation.x))
				{
					nextLoacation.x = moveinfo[current].targetLocation.x;  //到達後、目標を超えた場合停止
				}
			}
			else
			{
				nextLoacation.x -= speed.x;  //左方向
				direction = Direction::LEFT;

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
bool Enemy_Base::CheckHp()
{
	bool ret = (hp <= 0);
	return ret;
}

//プレイヤーの座標を取得
void Enemy_Base::SetTargetLocation(T_LOCATION location)
{
	target = location;
}


//csvファイル読み込み
void Enemy_Base::InputCSV(const char* pass)
{
	FILE* fp; /*FILE型構造体*/
	errno_t error; /*fopen_sのエラー確認*/
	error = fopen_s(&fp, pass, "r");

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


//発射する弾のスピードをセット    (対象の弾 , スピード)
void Enemy_Base::SetBulletsSpeed(Bullet_Type type, float speed)
{
	//対象の弾
	switch (type)
	{
	case Bullet_Type::Straight:     //ストレート

		speed_Straight = speed;
		break;

	case Bullet_Type::Vortex:       //回転

		speed_Vortex = speed;
		break;   

	case Bullet_Type::TakeAim:      //自機狙い

		speed_TakeAim = speed;
		break;  

	case Bullet_Type::Homing:       //ホーミング

		speed_Homing = speed;
		break;

	default:
		break;
	}

	return;
}