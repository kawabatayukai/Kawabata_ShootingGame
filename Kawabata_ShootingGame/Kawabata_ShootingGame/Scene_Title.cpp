#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_Title.h"
#include"Scene_GameMain.h"

//コンストラクタ
TitleScene::TitleScene()
{
	//画像読み込み
	image_back = LoadGraph("images/back.png");

	//フォントを作成
	font = CreateFontToHandle(NULL, 90, 20, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

//デストラクタ
TitleScene::~TitleScene()
{
	//フォントデータを削除
	DeleteFontToHandle(font);
}

//更新
void TitleScene::Update()
{
	//カーソル移動
	if (KeyManager::OnKeyClicked(KEY_INPUT_S)) menu_num++;
	if (menu_num > 1) menu_num = 0;
	if (KeyManager::OnKeyClicked(KEY_INPUT_W)) menu_num--;
	if (menu_num < 0) menu_num = 1;
}

//描画
void TitleScene::Draw() const
{
	//背景
	DrawGraph(0, 0, image_back, TRUE);

	//カーソル
	DrawCircle(420, (440 + (menu_num * 100)), 30, 0x00ff00, TRUE);

	DrawStringToHandle(300, 150, "Insect Fight", 0x00ff00, font, 0x000000);
	DrawStringToHandle(500, 400, "START", 0x00ff00, font, 0x000000);
	DrawStringToHandle(500, 500, " END ", 0x00ff00, font, 0x000000);
}

//シーンの変更
AbstractScene* TitleScene::ChangeScene()
{
	//スペースキーでシーン切り替え
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE) == true)
	{
		switch (menu_num)
		{
		case 0:   //ゲームメイン
			return dynamic_cast<AbstractScene*> (new GameMainScene());
			break;

		case 1:   //終了
			return nullptr;

		default:
			break;
		}

		
	}

	//更新なし
	return this;
}
