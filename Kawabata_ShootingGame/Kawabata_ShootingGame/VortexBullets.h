#pragma once
#include "BulletsBase.h"

//�Q
class VortexBullets : public BulletsBase
{
public:
	//�o���ʒu�̂݊O���@���a�E�_���[�W�E�X�s�[�h�͓����Őݒ�
	VortexBullets(T_LOCATION location, float speed, int angle, unsigned int color = GetColor(0, 200, 0));

	virtual void UpDate() override;           //�X�V
	virtual void Draw() override;             //�`��
	//virtual bool IsScreenOut() override;    //��ʊO/��

private:

	unsigned int color;   //�F
};

