#pragma once
#include "CharaBase.h"

//�ړ����@�G�̓���
struct MoveInfo
{
	int pattern;                 //����/�����Ȃ�
	T_LOCATION targetLocation;   //�ڕW
	int next;                    //���̓p�^�[���Z�Ԗ�
	int waitTime;                //
	int attackpattern;           //�U��/�U�����Ȃ�  0:�U�����Ȃ��@0<n:�U��
};

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

	void InputCSV();          //csv�t�@�C���ǂݍ���

private:
	int hp;
	int point;

	int shotNum;           //���˂�����
	int nowlocation;       //���݂̍��W�ԍ�

	MoveInfo moveinfo[10]; //�ړ��p�^�[��
	int current = 0;       //���݁Z�Ԗڂ̍��W
};

