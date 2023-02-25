#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_GameMain.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"Recovery.h"
#include"Enemy_01.h"
#include"Enemy_00.h"

//コンストラクタ
GameMainScene::GameMainScene()
{

	//オブジェクトを生成・メモリ確保・コンストラクタ呼び出し
	player = new Player(T_LOCATION{ P_INIT_X,P_INIT_Y });

	//Enemy10匹分のメモリを確保
	enemy = new Enemy_Base * [10];    
	
	for (int i = 0; i < 10; i++) enemy[i] = nullptr;    //初期化

	//初期座標・スピード（デフォルトで5）を設定
	enemy[0] = new Enemy_00(T_LOCATION{ 640,0 },T_LOCATION{ 4.f,4.f });       //Enemy00を生成
	enemy[1] = new Enemy_00(T_LOCATION{ -10,730 }, T_LOCATION{ 4.f,4.f });       //Enemy01を生成

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

	//プレイヤー移動範囲の制限
	float x = player->GetLocation().x;
	float y = player->GetLocation().y;
	float r = player->GetRadius();

	//左端
	if ((x - r) < 0)           player->SetLocation(T_LOCATION{ r,y });   
	//右端
	if ((x + r) > PLAY_AREA_W) player->SetLocation(T_LOCATION{ (PLAY_AREA_W - r),y });   
	//上端
	if ((y - r) < 0)           player->SetLocation(T_LOCATION{ x,r });
	//下端
	if ((y + r) > 720)         player->SetLocation(T_LOCATION{ x,(720 - r) });

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
	//player
	player->Draw();

	//Enemy
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] == nullptr) break;
		enemy[i]->Draw();
	}

	//Item
	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr) break;
		items[i]->Draw();
	}

	
	if (enemy[0] == nullptr)
	{
		DrawFormatString(100, 100, 0xffffff, "ステージ %d クリア", stage);
		DrawString(100, 130, "スペースキーで次へ", 0xffffff);
	}

	UI_Draw();
}

//シーンの変更
AbstractScene* GameMainScene::ChangeScene()
{
	//プレイヤー死亡でシーン切り替え
	if (player->LifeCheck() == true) return dynamic_cast<AbstractScene*>(new GameOverScene());


	//Enemy全滅で次のステージ
	if (enemy[0] == nullptr && stage < 4)
	{
		//初期化
		if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE))
		{
			Stage_Init(stage);
			stage++;
		}
		
	}

	if (enemy[0] == nullptr && stage == 4)
		return dynamic_cast<AbstractScene*>(new GameClearScene());


	//更新なし
	return this;
}

//ステージ変更
void GameMainScene::Stage_Init(int now_stage)
{
	//敵を初期化
	for (int i = 0; i < 10; i++) enemy[i] = nullptr;    

	//敵を生成（now_stage : 現在のステージ）
	switch (now_stage)
	{
	case 1:               //ステージ1の時、ステージ2へ
		enemy[0] = new Enemy_00(T_LOCATION{ 640,0 });
		enemy[1] = new Enemy_00(T_LOCATION{ 320,0 });
		enemy[2] = new Enemy_01(T_LOCATION{ 640,0 });
		enemy[3] = new Enemy_01(T_LOCATION{ 320,0 });
		break;

	case 2:
		enemy[0] = new Enemy_00(T_LOCATION{ 640,0 });
		enemy[1] = new Enemy_00(T_LOCATION{ 320,0 });
		enemy[2] = new Enemy_01(T_LOCATION{ 640,0 });
		enemy[3] = new Enemy_01(T_LOCATION{ 320,0 });
		enemy[4] = new Enemy_00(T_LOCATION{ 330,0 });
		enemy[5] = new Enemy_00(T_LOCATION{ 560,0 });
		enemy[6] = new Enemy_01(T_LOCATION{ 140,0 });
		enemy[7] = new Enemy_01(T_LOCATION{ 80,0 });
		break;

	default:
		break;
	}




	//プレイヤーの座標を初期化
	player->SetLocation(T_LOCATION{ P_INIT_X,P_INIT_Y });
}

//UI描画
void GameMainScene::UI_Draw() const
{
	DrawBox(PLAY_AREA_W, 0, 1280, 720, GetColor(0, 255, 0), TRUE);
	DrawBox(PLAY_AREA_W + 10 , 10, 1280 - 10, 720 - 10, GetColor(0, 0, 0), TRUE);
}