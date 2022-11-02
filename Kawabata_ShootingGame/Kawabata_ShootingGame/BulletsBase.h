#pragma once
#include "SphereCollider.h"

class BulletsBase : public SphereCollider
{
public:
	//コンストラクタ
	BulletsBase(T_LOCATION location, float radius,int damage,T_LOCATION speed);    

	//純粋仮想関数
	virtual void UpDate() = 0;           //更新
	virtual void Draw() = 0;             //描画

	virtual bool IsScreenOut() = 0;      //画面外か否か
	int GetDamage() { return damage; }   //ダメージ取得

protected:
	T_LOCATION speed;       //スピードxy

private:
	int damage;             //ダメージ
};

