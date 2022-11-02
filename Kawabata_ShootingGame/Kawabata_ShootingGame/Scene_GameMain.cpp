#include"DxLib.h"
#include"Scene_GameMain.h"

//コンストラクタ
GameMainScene::GameMainScene()
{
	T_LOCATION location = T_LOCATION{ 20,100 };

	//オブジェクトを生成・アドレス確保・コンストラクタ呼び出し
	player = new Player(location);

	enemy = new Enemy * [10];   //10匹分のメモリを確保
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
	enemy[0] = new Enemy(T_LOCATION{ 200,0 });
}

//デストラクタ
GameMainScene::~GameMainScene()
{
	//delete player;
}

//更新
void GameMainScene::Update()
{
	player->UpDate();
	
	int enemyCount;
	BulletsBase** bullet = player->GetBullets();   //所持している弾を取得

	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)	break;       //nullptrの要素より後には要素ﾅｼ
		enemy[enemyCount]->UpDate();

		//敵と弾の当たり判定
		for (int bulletCount = 0; bulletCount < 30; bulletCount++)
		{
			if (bullet[bulletCount] == nullptr) break;   //nullptrの要素より後には要素ﾅｼ

			//SphereCollider同士の当たり判定
			if ( enemy[enemyCount]->HitSphere( bullet[bulletCount]) )
			{
				//敵に弾がヒット

				//敵にダメージが入る
				enemy[enemyCount]-> Hit( bullet[bulletCount]->GetDamage() );

				//弾を削除
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//敵のHP <= 0 削除する
				if (enemy[enemyCount]->CheckHp())
				{
					delete enemy[enemyCount];
					enemy[enemyCount] = nullptr;

					//詰める
					for (int i = enemyCount; i < (10 - 1); i++)
					{
						if (enemy[i + 1] == nullptr) break;
						enemy[i] = enemy[i + 1];
						enemy[i + 1] = nullptr;                //詰めた元を初期化
					}
					enemyCount--;
				}

			}
		}

	}
}

//描画（　^ ω ^）
void GameMainScene::Draw() const
{
	player->Draw();
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] == nullptr) break;
		enemy[i]->Draw();
	}
}

//シーンの変更
AbstractScene* GameMainScene::ChangeScene()
{
	//if(player->LifeCheck()==true) return dynamic_cast<AbstractScene*>(new TitleS)

	//更新なし
	return this;
}