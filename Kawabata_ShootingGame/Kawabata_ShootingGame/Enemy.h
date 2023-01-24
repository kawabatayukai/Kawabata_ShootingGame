#pragma once
#include "CharaBase.h"

class Enemy : public CharaBase
{
public:
	Enemy(T_LOCATION location = {640,0});

	virtual void UpDate() override;  //�X�V
	virtual void Draw()   override;  //�`��
	virtual void Hit(int damage)    override;  //������i�_���[�W�j

	void Move();              //���̈ړ�

	bool CheckHp();           //Hp���`�F�b�N
	int GetPoint() { return point; }           //�|�C���g�擾

private:
	int hp;
	int point;

	int shotNum;   //���˂�����
	int nowlocation; //���݂̍��W�ԍ�

	
};

