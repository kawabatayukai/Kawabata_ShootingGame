#pragma once
#include "SphereCollider.h"

class BulletsBase : public SphereCollider
{
public:
	//�R���X�g���N�^
	BulletsBase(T_LOCATION location, float radius,int damage,T_LOCATION speed);    

	//�������z�֐�
	virtual void UpDate() = 0;           //�X�V
	virtual void Draw() = 0;             //�`��

	virtual bool IsScreenOut() = 0;      //��ʊO���ۂ�
	int GetDamage() { return damage; }   //�_���[�W�擾

protected:
	T_LOCATION speed;       //�X�s�[�hxy

private:
	int damage;             //�_���[�W
};

