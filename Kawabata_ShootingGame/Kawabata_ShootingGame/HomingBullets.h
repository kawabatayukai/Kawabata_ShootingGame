#pragma once
#include"BulletsBase.h"

//�z�[�~���O
class HomingBullets : public BulletsBase
{
public:
	//�R���X�g���N�^
	HomingBullets(T_LOCATION location, float speed);

	void Update() override;           //�X�V
	void Draw() override;             //�`��

private:
	double angle;                     //�p�x
	int time_counter = 0;             //�ǐՎ��Ԃ��J�E���g

	int image;                        //�摜
};