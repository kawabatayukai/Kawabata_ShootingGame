#pragma once
#include "CharaBase.h"

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

private:
	int hp;
	int point;

	int shotNum;   //発射した数
	int nowlocation; //現在の座標番号

	
};

