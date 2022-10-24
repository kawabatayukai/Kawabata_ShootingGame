#pragma once
#include"SphereCollider.h"
#include"BulletsBase.h"

//�L�����̊��N���X
class CharaBase : public SphereCollider
{
public:
	CharaBase(T_LOCATION location, float radius, T_LOCATION speed);

	virtual void UpDate() = 0;    //�X�V
	virtual void Draw() = 0;      //�`��
	virtual void Hit() = 0;       //�����������̏���

	BulletsBase** GetBullets();   //

protected:
	int* image;
	BulletsBase** bullets;        //�|�C���^�z��

private:


	T_LOCATION speed;
};

