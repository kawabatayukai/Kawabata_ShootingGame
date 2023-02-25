#pragma once
#include"AbstractScene.h"
#include"Player.h"
#include"Enemy_Base.h"
#include"ItemBase.h"

//ゲームプレイ領域
#define PLAY_AREA_W 1100

//プレイヤー初期座標
#define P_INIT_X    640.0f
#define P_INIT_Y    500.0f

//ゲームメイン
class GameMainScene : public AbstractScene
{
public:
	
	GameMainScene();              //コンストラクタ
	
	~GameMainScene();             //デストラクタ     
	
	void Update() override;                //更新
	void Draw() const override;            //描画

	AbstractScene* ChangeScene() override; //シーンの変更

	void Stage_Init(int now_stage);        //ステージ変更

	void UI_Draw() const;                  //UI描画

private:
	Player* player;
	Enemy_Base** enemy;
	ItemBase** items;

	int stage = 1;    //ステージカウント変数
};
