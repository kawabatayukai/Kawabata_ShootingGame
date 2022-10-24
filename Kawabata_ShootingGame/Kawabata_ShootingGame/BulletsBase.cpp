#include "BulletsBase.h"

//コンストラクタ               位置　　　　　　　　半径　　　　ダメージ　　　スピード
BulletsBase::BulletsBase(T_LOCATION location, float radius, int damage, T_LOCATION speed)  
	:SphereCollider(location,radius),damage(damage),speed(speed)           //SphereCollider　のコンストラクタを呼び出し
{
}
