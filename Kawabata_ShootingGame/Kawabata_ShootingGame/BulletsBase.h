#pragma once
#include "SphereCollider.h"

//弾の種類
enum class Bullet_Type
{
	Straight,   //ストレート
	Vortex,     //回転
	TakeAim,    //自機狙い
	Homing,     //ホーミング
};


class BulletsBase : public SphereCollider
{
public:
	//コンストラクタ
	BulletsBase(T_LOCATION location, float radius,int damage,T_LOCATION speed);    

	//純粋仮想関数
	virtual void Update() = 0;           //更新
	virtual void Draw() = 0;             //描画

	bool IsScreenOut();                  //画面外か否か
	int GetDamage() { return damage; }   //ダメージ取得

	//ターゲット(プレイヤー)の座標をセット
	void SetTargetLocation(T_LOCATION location);

protected:
	T_LOCATION speed;       //スピードxy
	T_LOCATION target;      //ターゲット(プレイヤー)の座標

private:
	int damage;             //ダメージ
};

