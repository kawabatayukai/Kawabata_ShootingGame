#pragma once
#include"SphereCollider.h"

//�L�����̊��N���X
class CharaBase : public SphereCollider
{
public:
	CharaBase(T_LOCATION location, float radius, T_LOCATION speed);

	virtual void UpDate() = 0;    //�X�V
	virtual void Draw() = 0;      //�`��
	virtual void Hit() = 0;       //�����������̏���

	//GetBullets();

protected:
	int* image;

private:
	//bullets �|�C���^�z��
	T_LOCATION speed;
};

