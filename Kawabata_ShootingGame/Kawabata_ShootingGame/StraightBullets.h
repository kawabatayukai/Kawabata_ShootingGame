#pragma once
#include "BulletsBase.h"

//�X�g���[�g
class StraightBullets : public BulletsBase
{
public:
	//�o���ʒu�̂݊O���@���a�E�_���[�W�E�X�s�[�h�͓����Őݒ�
	StraightBullets(T_LOCATION location);

	virtual void UpDate() override;           //�X�V
	virtual void Draw() override;             //�`��

private:

};

