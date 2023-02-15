#include"DxLib.h"
#include"Scene_GameMain.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"Recovery.h"
#include"Enemy_01.h"
#include"Enemy_00.h"

//コンストラクタ
GameMainScene::GameMainScene()
{
	T_LOCATION location = T_LOCATION{ 20,100 };

	//オブジェクトを生成・アドレス確保・コンストラクタ呼び出し
	player = new Player(location);

	//Enemy10匹分のメモリを確保
	enemy = new Enemy_Base * [10];    
	
	for (int i = 0; i < 10; i++) enemy[i] = nullptr;    //初期化

	//初期座標・スピード（デフォルトで5）を設定
	enemy[0] = new Enemy_00(T_LOCATION{ 640,0 });       //Enemy00を生成
	enemy[1] = new Enemy_01(T_LOCATION{ 320,0 });       //Enemy01を生成
	enemy[2] = new Enemy_00(T_LOCATION{ 820,730 }, T_LOCATION{1.f,1.f});       //Enemy01を生成
	enemy[3] = new Enemy_01(T_LOCATION{ 120,0 }, T_LOCATION{20.f,20.f});       //Enemy01を生成

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
	player->Update();

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
		enemy[enemyCount]->Update();

		//プレイヤーの座標を取得
		enemy[enemyCount]->SetTargetLocation(player->GetLocation());  

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
}

//シーンの変更
AbstractScene* GameMainScene::ChangeScene()
{
	//プレイヤー死亡でシーン切り替え
	if (player->LifeCheck() == true) return dynamic_cast<AbstractScene*>(new GameOverScene());

	//Enemy全滅でシーン切り替え
	if(enemy[0]==nullptr) return dynamic_cast<AbstractScene*>(new GameClearScene());


	//更新なし
	return this;
}