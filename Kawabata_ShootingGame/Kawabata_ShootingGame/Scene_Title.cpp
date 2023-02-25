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
	font = CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
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

}

//描画
void TitleScene::Draw() const
{
	//背景
	DrawGraph(0, 0, image_back, TRUE);

	DrawString(100, 70, "タイトル", 0xffffff);
	DrawString(100, 170, "スペースキーでスタート", 0xffffff);
}

//シーンの変更
AbstractScene* TitleScene::ChangeScene()
{
	//スペースキーでシーン切り替え
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE) == true)
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
	}

	//更新なし
	return this;
}
