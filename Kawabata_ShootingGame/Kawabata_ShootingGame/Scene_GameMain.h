#pragma once
#include"AbstractScene.h"
#include"Player.h"
#include"Enemy_Base.h"
#include"ItemBase.h"

//ゲームメイン
class GameMainScene : public AbstractScene
{
public:
	
	GameMainScene();              //コンストラクタ
	
	~GameMainScene();             //デストラクタ     
	
	void Update() override;  //更新
	
	void Draw() const override;        //描画

	AbstractScene* ChangeScene() override; //シーンの変更

private:
	Player* player;
	Enemy_Base** enemy;
	ItemBase** items;
};
