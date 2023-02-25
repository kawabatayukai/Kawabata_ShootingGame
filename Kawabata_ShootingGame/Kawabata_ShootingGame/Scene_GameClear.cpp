#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameClear.h"
#include"Scene_Title.h"

//コンストラクタ
GameClearScene::GameClearScene()
{
	//画像読み込み
	image_back = LoadGraph("images/back.png");

	//フォントを作成
	font = CreateFontToHandle(NULL, 150, 20, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2);
	font1 = CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

//デストラクタ
GameClearScene::~GameClearScene()
{
	//フォントデータを削除
	DeleteFontToHandle(font);
	DeleteFontToHandle(font1);
}

//更新
void GameClearScene::Update()
{

}



//描画
void GameClearScene::Draw() const
{
	//背景
	DrawGraph(0, 0, image_back, TRUE);

	DrawStringToHandle(280, 150, "Game Clear", 0xffa500, font, 0x000000);
	DrawStringToHandle(380, 500, "Press Space To Title", 0xffa500, font1, 0x000000);
}

//シーンの変更
AbstractScene* GameClearScene::ChangeScene()
{
	//スペースキーでシーン切り替え
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE) == true)
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}

	//更新なし
	return this;
}
