#include "BulletsBase.h"

//�R���X�g���N�^               �ʒu�@�@�@�@�@�@�@�@���a�@�@�@�@�_���[�W�@�@�@�X�s�[�h
BulletsBase::BulletsBase(T_LOCATION location, float radius, int damage, T_LOCATION speed)  
	:SphereCollider(location,radius),damage(damage),speed(speed)           //SphereCollider�@�̃R���X�g���N�^���Ăяo��
{
}
