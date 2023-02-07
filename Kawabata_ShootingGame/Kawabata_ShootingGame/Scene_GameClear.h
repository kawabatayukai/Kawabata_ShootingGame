#pragma once
#include "AbstractScene.h"

//タイトル
class GameClearScene : public AbstractScene
{
public:
	GameClearScene();
	~GameClearScene();           //デストラクタ

	void Update() override;            //更新

	void Draw() const override;        //描画

	AbstractScene* ChangeScene() override; //シーンの変更
};

