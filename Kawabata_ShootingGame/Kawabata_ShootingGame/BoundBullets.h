#pragma once
#include"BulletsBase.h"

//�o�E���h
class BoundBullets : public BulletsBase
{
public:
	//�R���X�g���N�^
	BoundBullets(T_LOCATION location, float speed);

	void UpDate() override;           //�X�V
	void Draw() override;             //�`��

private:
	float angle;               //�p�x
};