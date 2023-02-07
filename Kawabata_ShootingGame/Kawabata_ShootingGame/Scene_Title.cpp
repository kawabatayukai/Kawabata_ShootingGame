#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_Title.h"
#include"Scene_GameMain.h"

//コンストラクタ
TitleScene::TitleScene()
{
	SetFontSize(50);
}

//デストラクタ
TitleScene::~TitleScene()
{
	SetFontSize(10);
}

//更新
void TitleScene::Update()
{

}

//描画
void TitleScene::Draw() const
{
	//
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
