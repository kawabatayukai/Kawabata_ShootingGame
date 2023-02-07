#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameClear.h"
#include"Scene_Title.h"

//コンストラクタ
GameClearScene::GameClearScene()
{
	SetFontSize(50);
}

//デストラクタ
GameClearScene::~GameClearScene()
{
	SetFontSize(10);
}

//更新
void GameClearScene::Update()
{

}



//描画
void GameClearScene::Draw() const
{
	//
	DrawString(100, 70, "Game Clear", 0xffffff);
	DrawString(100, 170, "スペースキーでタイトルへ", 0xffffff);
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
