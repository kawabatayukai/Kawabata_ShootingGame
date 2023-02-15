#pragma once
#include "CharaBase.h"
#include"Enemy_Base.h"

//�g���Ă��Ȃ�


class Enemy : public CharaBase
{
public:
	//�R���X�g���N�^
	Enemy(T_LOCATION location = {640,0},int HP = 10,const char* pass = "CSV/moveinfo.csv");

	virtual void Update() override;  //�X�V
	virtual void Draw()   override;  //�`��
	void Hit(int damage)  override;  //������i�_���[�W�j

	void Move();              //���̈ړ�
	bool CheckHp();           //Hp���`�F�b�N
	int GetPoint() { return point; }          //�|�C���g�擾

	//�v���C���[�̍��W�����炤
	void SetTargetLocation(T_LOCATION location);
	void InputCSV(const char* pass);          //csv�t�@�C���ǂݍ���

private:

	int shotNum = 0;       //���˂�����
	
	MoveInfo moveinfo[10]; //�ړ��p�^�[��
	int current = 0;       //���݃p�^�[���Z�Ԗ�

protected:
	int hp;                //HP
	int point;             //���_
	int image = 0;         //�摜
	int color = 0;
	T_LOCATION target = { 0,0 };
};

