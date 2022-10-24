#include"DxLib.h"
#include"Scene_GameMain.h"

//コンストラクタ
GameMainScene::GameMainScene()
{
	T_LOCATION location = T_LOCATION{ 20,100 };

	//オブジェクトを生成・アドレス確保・コンストラクタ呼び出し
	player = new Player(location);
}

//デストラクタ
GameMainScene::~GameMainScene()
{
	//delete player;
}

//更新
void GameMainScene::Update()
{
	//T_LOCATION location = T_LOCATION{ 100,100 };
	//Player test = Player(location);
	////test.Draw();

	/*if (test.HitSphere(player)) return;*/
	player->UpDate();
}

//描画
void GameMainScene::Draw() const
{
	player->Draw();
}

//シーンの変更
AbstractScene* GameMainScene::ChangeScene()
{
	//if(player->LifeCheck()==true) return dynamic_cast<AbstractScene*>(new TitleS)

	//更新なし
	return this;
}