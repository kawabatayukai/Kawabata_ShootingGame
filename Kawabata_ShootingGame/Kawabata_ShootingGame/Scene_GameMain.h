#pragma once
#include"AbstractScene.h"

//ゲームメイン
class GameMainScene : public AbstractScene
{
public:
	
	GameMainScene();              //コンストラクタ
	
	virtual ~GameMainScene() {}   //デストラクタ     
	
	void Update() override;  //更新
	
	void Draw() const override;        //描画

	AbstractScene* ChangeScene() override; //シーンの変更
};
