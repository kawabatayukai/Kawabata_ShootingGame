#include "ItemBase.h"


//コンストラクタ
ItemBase::ItemBase(T_LOCATION location, float radius, E_ITEM_TYPE type, T_LOCATION speed)
	: SphereCollider(location, radius), type(type), speed(speed)
{

}

//タイプ取得
E_ITEM_TYPE ItemBase::GetType() const
{
	return type;
}
