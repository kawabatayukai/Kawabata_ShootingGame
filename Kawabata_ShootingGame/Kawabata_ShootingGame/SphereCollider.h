#pragma once
#include"common.h"

//�����蔻��
class SphereCollider
{
public:
	SphereCollider(T_LOCATION location, float radius);
	//~SphereCollider();

public:
	//SphereCollider���m�̓����蔻��
	bool HitSphere(const SphereCollider* collider) const;

	T_LOCATION GetLocation() const;             //���S���W�擾
	void SetLocation(T_LOCATION location);      //���W���Z�b�g
	float GetRadius() const;                    //���a�擾

private:

	T_LOCATION location;   //���S���W
	float radius;          //���a
};

