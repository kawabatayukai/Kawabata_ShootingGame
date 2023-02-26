#pragma once
#include "SphereCollider.h"

//�e�̎��
enum class Bullet_Type
{
	Straight,   //�X�g���[�g
	Vortex,     //��]
	TakeAim,    //���@�_��
	Homing,     //�z�[�~���O
};


class BulletsBase : public SphereCollider
{
public:
	//�R���X�g���N�^
	BulletsBase(T_LOCATION location, float radius,int damage,T_LOCATION speed);    

	//�������z�֐�
	virtual void Update() = 0;           //�X�V
	virtual void Draw() = 0;             //�`��

	bool IsScreenOut();                  //��ʊO���ۂ�
	int GetDamage() { return damage; }   //�_���[�W�擾

	//�^�[�Q�b�g(�v���C���[)�̍��W���Z�b�g
	void SetTargetLocation(T_LOCATION location);

protected:
	T_LOCATION speed;       //�X�s�[�hxy
	T_LOCATION target;      //�^�[�Q�b�g(�v���C���[)�̍��W

private:
	int damage;             //�_���[�W
};

