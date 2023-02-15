#pragma once
#include "CharaBase.h"
#include"Enemy_Base.h"

//使っていない


class Enemy : public CharaBase
{
public:
	//コンストラクタ
	Enemy(T_LOCATION location = {640,0},int HP = 10,const char* pass = "CSV/moveinfo.csv");

	virtual void Update() override;  //更新
	virtual void Draw()   override;  //描画
	void Hit(int damage)  override;  //当たり（ダメージ）

	void Move();              //一定の移動
	bool CheckHp();           //Hpをチェック
	int GetPoint() { return point; }          //ポイント取得

	//プレイヤーの座標をもらう
	void SetTargetLocation(T_LOCATION location);
	void InputCSV(const char* pass);          //csvファイル読み込み

private:

	int shotNum = 0;       //発射した数
	
	MoveInfo moveinfo[10]; //移動パターン
	int current = 0;       //現在パターン〇番目

protected:
	int hp;                //HP
	int point;             //得点
	int image = 0;         //画像
	int color = 0;
	T_LOCATION target = { 0,0 };
};

