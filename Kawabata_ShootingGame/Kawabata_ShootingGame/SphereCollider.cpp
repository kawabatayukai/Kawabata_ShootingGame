#include"DxLib.h"
#include<math.h>
#include "SphereCollider.h"

//�R���X�g���N�^
SphereCollider::SphereCollider(T_LOCATION location, float radius)
{
	this->location = location;
	this->radius = radius;
}

//SphereCollider���m�̓����蔻��
bool SphereCollider::HitSphere(const SphereCollider* collider) const
{
	//�������瑊��ւ̃x�N�g�����v�Z����
	//�v�Z�ŏo�����x�N�g���̑傫���Ǝ����Ƒ���̔��a�̍��v���
	//�x�N�g���̑傫������������΂�����
	
	//�����Ƒ���Ԃ̃x�N�g�����v�Z
	float vectrX = fabsf(this->location.x - collider->GetLocation().x);    //x���W�̍���
	float vectrY = fabsf(this->location.y - collider->GetLocation().y);    //y���W�̍���
	float vectrLength = sqrtf((vectrX * vectrX) + (vectrY * vectrY));      //2�̉~�̋���  �x�N�g���̑傫�����v�Z

	//�����Ƒ���Ԃ̃x�N�g���Ɣ��a�̍��v���r
	if (vectrLength < (this->radius + collider->GetRadius())) return true;
	else return false;
}

//���S���W�擾
T_LOCATION SphereCollider::GetLocation() const { return location; }

//���W���Z�b�g
void SphereCollider::SetLocation(T_LOCATION location) { this->location = location; }

//���a�擾
float SphereCollider::GetRadius() const { return radius; }
