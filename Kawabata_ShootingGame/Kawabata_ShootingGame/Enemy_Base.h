#pragma once
#include"CharaBase.h"

#define BULLETS_MAX 100

//�ړ����@�G�̓���
struct MoveInfo
{
	int pattern;                 //����/�����Ȃ�
	T_LOCATION targetLocation;   //�ڕW
	int next;                    //���̓p�^�[���Z�Ԗ�
	int waitTime;                //
	int attackpattern;           //�U��/�U�����Ȃ�  0:�U�����Ȃ��@0<n:�U��
};

//����
enum class Direction
{
	LEFT,      //��
	RIGHT      //�E
};

//�G�L�����̊��N���X
class Enemy_Base : public CharaBase
{
public:
	//�R���X�g���N�^    ���W�A���a�A�X�s�[�h�Acsv�̃p�X��ݒ�
	Enemy_Base(T_LOCATION location, float radius, T_LOCATION speed, const char* pass = nullptr);

	void Update() override;          //�X�V
	virtual void Draw()   override;  //�`��
	void Hit(int damage)  override;  //������i�_���[�W�j

	void Move();                     //���̈ړ�
	bool CheckHp();                  //Hp���`�F�b�N
	int GetPoint() { return point; } //�|�C���g�擾

	//�v���C���[�̍��W�����炤
	void SetTargetLocation(T_LOCATION location);

	//csv�t�@�C���ǂݍ���
	void InputCSV(const char* pass);          

private:

	int shotNum = 0;       //���˂�����
	int frame_count = 0;   //�t���[�����J�E���g

	MoveInfo moveinfo[10]; //�ړ��p�^�[��
	int current = 0;       //���݁Z�Ԗڂ̍��W
	T_LOCATION target = { 0,0 };

protected:
	int hp = 0;            //HP
	int point = 0;         //���_

	int image = 0; //�摜

	Direction direction;   //����
};
