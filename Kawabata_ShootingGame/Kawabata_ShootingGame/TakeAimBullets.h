#pragma once
#include"BulletsBase.h"

// �_���Ă�����
class TakeAimBullets : public BulletsBase
{
public:
	//�o���ʒu�A�v���C���[�̍��W�A�X�s�[�h
	TakeAimBullets(T_LOCATION location, T_LOCATION p_location, float speed);

	void UpDate() override;           //�X�V
	void Draw() override;             //�`��

	//�������W�ƖڕW���W�Ƃ̊p�x�����߂�
	float GetRadian(T_LOCATION self, T_LOCATION target);

private:
	int image;    //�摜
};

