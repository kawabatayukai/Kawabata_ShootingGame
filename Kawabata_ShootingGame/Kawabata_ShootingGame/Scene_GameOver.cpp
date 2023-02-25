#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameOver.h"
#include"Scene_Title.h"

//コンストラクタ
GameOverScene::GameOverScene()
{
	//画像読み込み
	image_back = LoadGraph("images/back.png");

	//フォントを作成
	font = CreateFontToHandle(NULL, 150, 20, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2);
	font1 = CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

//デストラクタ
GameOverScene::~GameOverScene()
{
	//フォントデータを削除
	DeleteFontToHandle(font);
	DeleteFontToHandle(font1);
}

//更新
void GameOverScene::Update()
{
	
}



//描画
void GameOverScene::Draw() const
{
	//背景
	DrawGraph(0, 0, image_back, TRUE);

	DrawStringToHandle(280, 150, "Game Over", 0xffa500, font, 0x000000);
	DrawStringToHandle(380, 500, "Press Space To Title", 0xffa500, font1, 0x000000);
}

//シーンの変更
AbstractScene* GameOverScene::ChangeScene()
{
	//スペースキーでシーン切り替え
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE) == true)
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}

	//更新なし
	return this;
}
