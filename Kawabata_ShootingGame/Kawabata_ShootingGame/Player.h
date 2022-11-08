#pragma once
#include "CharaBase.h"

//�v���C���[�N���X
class Player : public CharaBase
{
public:
	Player(T_LOCATION location);                //�R���X�g���N�^

	void UpDate() override;  //�X�V
	void Draw() override;    //�`��
	void Hit(int damage) override;     //�����������̏���
	
	bool LifeCheck();                  //"life"���m�F
	int GetScore() const;              //�X�R�A�擾
	void AddScore(int score);          //�X�R�A���Z

private:
	int score;
	int life;
};

