#include"DxLib.h"
#include"Scene_GameMain.h"
#include"Recovery.h"

//コンストラクタ
GameMainScene::GameMainScene()
{
	T_LOCATION location = T_LOCATION{ 20,100 };

	//オブジェクトを生成・アドレス確保・コンストラクタ呼び出し
	player = new Player(location);

	//10匹分のメモリを確保
	enemy = new Enemy * [10];
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
	//enemy[0] = new Enemy(T_LOCATION{ 600,300 });
	enemy[0] = new Enemy();

	//Item 10個分のメモリを確保
	items = new ItemBase * [10];
	for (int i = 0; i < 10; i++) items[i] = nullptr;
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
	
	//Item更新
	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr) break;
		items[i]->UpDate();
	}

	//Enemyとプレイヤーの弾の当たり判定
	BulletsBase** bullet = player->GetBullets();   //所持している弾を取得
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		//Enemy更新
		if (enemy[enemyCount] == nullptr)	break;       //nullptrの要素より後には要素ﾅｼ
		enemy[enemyCount]->UpDate();

		//敵と弾の当たり判定
		for (int bulletCount = 0; bulletCount < 100; bulletCount++)
		{
			if (bullet[bulletCount] == nullptr) break;   //nullptrの要素より後には要素ﾅｼ

			//SphereCollider同士の当たり判定
			if (enemy[enemyCount]->HitSphere(bullet[bulletCount]))
			{
				//敵に弾がヒット

				//敵にダメージが入る
				enemy[enemyCount]->Hit(bullet[bulletCount]->GetDamage());

				//弾を削除
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//敵のHP <= 0 削除する
				if (enemy[enemyCount]->CheckHp() == true)
				{
					for (int i = 0; i < 10; i++)
					{
						if (items[i] == nullptr)
						{
							items[i] = new Recovery(enemy[enemyCount]->GetLocation());
							break;
						}
					}

					//スコア加算
					player->AddScore(enemy[enemyCount]->GetPoint());

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
					break;
				}
			}
		}
	}

	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr) break;
		bullet= enemy[enemyCount]->GetBullets();    //敵の保持する弾

		for (int bulletCount = 0; bulletCount < 100; bulletCount++)
		{
			if (bullet[bulletCount] == nullptr) break;   //nullptrの要素より後には要素ﾅｼ

			//SphereCollider同士の当たり判定
			if (player->HitSphere(bullet[bulletCount]))
			{
				//プレイヤーにダメージを与える
				player->Hit(bullet[bulletCount]->GetDamage());

				//弾を削除
				enemy[enemyCount]->DeleteBullet(bulletCount);
				bulletCount--;
				break;
			}
		}
	}

	//ItemとPlayerの当たり判定
	for (int itemCount = 0; itemCount < 10; itemCount++)
	{
		if (items[itemCount] == nullptr) break;   //nullptrの要素より後には要素ﾅｼ

		if (items[itemCount]->HitSphere(player) == true)
		{
			//アイテムの効果を反映
			player->Hit(items[itemCount]);

			delete items[itemCount];
			items[itemCount] = nullptr;

			//配列を詰める
			for (int i = itemCount; i < (10 - 1); i++)
			{
				if (items[itemCount] == nullptr) break;
				items[i] = items[i + 1];
				items[i + 1] = nullptr;                //詰めた元を初期化
			}
			itemCount--;
		}
	}

}

//描画
void GameMainScene::Draw() const
{
	player->Draw();
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] == nullptr) break;
		enemy[i]->Draw();
	}

	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr) break;
		items[i]->Draw();
	}

	DrawFormatString(0, 0, 0xffffff, "%f %f", enemy[0]->GetLocation().x, enemy[0]->GetLocation().y);
}

//シーンの変更
AbstractScene* GameMainScene::ChangeScene()
{
	//if(player->LifeCheck()==true) return dynamic_cast<AbstractScene*>(new TitleS)

	//更新なし
	return this;
}