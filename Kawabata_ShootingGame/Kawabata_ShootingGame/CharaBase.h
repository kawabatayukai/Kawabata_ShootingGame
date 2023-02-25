#pragma once
#include"SphereCollider.h"
#include"BulletsBase.h"

//�L�����̊��N���X
class CharaBase : public SphereCollider
{
public:
	CharaBase(T_LOCATION location, float radius, T_LOCATION speed);

	virtual void Update() = 0;    //�X�V
	virtual void Draw() = 0;      //�`��
	virtual void Hit(int damage) = 0;       //�����������̏���

	BulletsBase** GetBullets();             //�e�z��擾

	void DeleteBullet(int bulletNum);       //�w�肳�ꂽ�v�f�ԍ��̒e���폜

protected:

	BulletsBase** bullets;        //�|�C���^�z��
	T_LOCATION speed;

private:


	
};

