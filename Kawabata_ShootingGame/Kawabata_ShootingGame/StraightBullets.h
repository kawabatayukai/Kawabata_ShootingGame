#pragma once
#include "BulletsBase.h"

//�X�g���[�g
class StraightBullets : public BulletsBase
{
public:
	//�o���ʒu�̂݊O���@���a�E�_���[�W�E�X�s�[�h�͓����Őݒ�
	StraightBullets(T_LOCATION location, T_LOCATION speed);

	virtual void UpDate() override;           //�X�V
	virtual void Draw() override;             //�`��

	virtual bool IsScreenOut() override;      //��ʊO/��

private:

};

