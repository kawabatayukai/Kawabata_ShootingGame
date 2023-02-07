#pragma once
#include "CharaBase.h"

//移動情報　敵の動き
struct MoveInfo
{
	int pattern;                 //動く/動かない
	T_LOCATION targetLocation;   //目標
	int next;                    //次はパターン〇番目
	int waitTime;                //
	int attackpattern;           //攻撃/攻撃しない  0:攻撃しない　0<n:攻撃
};

class Enemy : public CharaBase
{
public:
	Enemy(T_LOCATION location = {640,0});

	virtual void UpDate() override;  //更新
	virtual void Draw()   override;  //描画
	virtual void Hit(int damage)    override;  //当たり（ダメージ）

	void Move();              //一定の移動

	bool CheckHp();           //Hpをチェック
	int GetPoint() { return point; }           //ポイント取得

	void InputCSV();          //csvファイル読み込み

private:
	int hp;
	int point;

	int shotNum;           //発射した数
	int nowlocation;       //現在の座標番号

	MoveInfo moveinfo[10]; //移動パターン
	int current = 0;       //現在〇番目の座標
};

