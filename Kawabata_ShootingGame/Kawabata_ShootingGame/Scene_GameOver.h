#pragma once
#include "AbstractScene.h"

//ゲームオーバー
class GameOverScene : public AbstractScene
{
public:
	//コンストラクタ（スコアをもらう）
	GameOverScene(int score = 0);
	~GameOverScene();           //デストラクタ

	void Update() override;            //更新

	void Draw() const override;        //描画

	AbstractScene* ChangeScene() override; //シーンの変更

private:
	int last_score;  //表示するスコア

	int image_back;  //画像
	int font;        //フォント
	int font1;
};

