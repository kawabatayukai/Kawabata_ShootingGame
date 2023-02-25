#pragma once
#include "AbstractScene.h"

//ゲームオーバー
class GameOverScene : public AbstractScene
{
public:
	GameOverScene();
	~GameOverScene();           //デストラクタ

	void Update() override;            //更新

	void Draw() const override;        //描画

	AbstractScene* ChangeScene() override; //シーンの変更

private:
	int image_back;  //画像
	int font;        //フォント
};

