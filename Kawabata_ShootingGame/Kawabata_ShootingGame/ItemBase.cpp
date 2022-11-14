#include "ItemBase.h"


//�R���X�g���N�^
ItemBase::ItemBase(T_LOCATION location, float radius, E_ITEM_TYPE type, T_LOCATION speed)
	: SphereCollider(location, radius), type(type), speed(speed)
{

}

//�^�C�v�擾
E_ITEM_TYPE ItemBase::GetType() const
{
	return type;
}
