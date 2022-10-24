#pragma once
#include"common.h"

//当たり判定
class SphereCollider
{
public:
	SphereCollider(T_LOCATION location, float radius);
	//~SphereCollider();

public:
	//SphereCollider同士の当たり判定
	bool HitSphere(const SphereCollider* collider) const;

	T_LOCATION GetLocation() const;             //中心座標取得
	void SetLocation(T_LOCATION location);      //座標をセット
	float GetRadius() const;                    //半径取得

private:

	T_LOCATION location;   //中心座標
	float radius;          //半径
};

