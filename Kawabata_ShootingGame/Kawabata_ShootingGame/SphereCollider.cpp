#include"DxLib.h"
#include<math.h>
#include "SphereCollider.h"

//コンストラクタ
SphereCollider::SphereCollider(T_LOCATION location, float radius)
{
	this->location = location;
	this->radius = radius;
}

//SphereCollider同士の当たり判定
bool SphereCollider::HitSphere(const SphereCollider* collider) const
{
	//自分と相手間のベクトルを計算
	float vectrX = fabsf(this->location.x - collider->GetLocation().x);    //x座標の差分
	float vectrY = fabsf(this->location.y - collider->GetLocation().y);    //y座標の差分
	float vectrLength = sqrtf((vectrX * vectrX) + (vectrY * vectrY));      //2つの円の距離  ベクトルの大きさを計算

	//自分と相手間のベクトルと半径の合計を比較
	//if (vectrLength < (this->radius + collider->GetRadius())) return true;
	//else return false;

	bool ret = (vectrLength < (this->radius + collider->GetRadius()));

	return ret;
}

//中心座標取得
T_LOCATION SphereCollider::GetLocation() const { return location; }

//座標をセット
void SphereCollider::SetLocation(T_LOCATION location) { this->location = location; }

//半径取得
float SphereCollider::GetRadius() const { return radius; }
