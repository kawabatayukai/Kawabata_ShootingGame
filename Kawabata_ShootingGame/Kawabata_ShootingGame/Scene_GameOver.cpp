#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameOver.h"
#include"Scene_Title.h"

//コンストラクタ
GameOverScene::GameOverScene()
{
	SetFontSize(50);
}

//デストラクタ
GameOverScene::~GameOverScene()
{
	SetFontSize(10);
}

//更新
void GameOverScene::Update()
{
	
}



//描画
void GameOverScene::Draw() const
{
	//
	DrawString(100, 70, "Game Over", 0xffffff);
	DrawString(100, 170, "スペースキーでタイトルへ", 0xffffff);
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
