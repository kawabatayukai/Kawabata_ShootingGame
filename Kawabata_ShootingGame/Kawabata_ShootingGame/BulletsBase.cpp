#include "BulletsBase.h"

//コンストラクタ               位置　　　　　　　　半径　　　　ダメージ　　　スピード
BulletsBase::BulletsBase(T_LOCATION location, float radius, int damage, T_LOCATION speed)  
	:SphereCollider(location,radius),damage(damage),speed(speed)           //SphereCollider　のコンストラクタを呼び出し
{
}

//画面外か否か
bool BulletsBase::IsScreenOut()
{
	bool ret = ((GetLocation().y + GetRadius()) <= 0 || (GetLocation().y - GetRadius() >= 720) || (GetLocation().x + GetRadius()) <= 0 || (GetLocation().x - GetRadius()) >= 1280);
	return ret;
}
