#pragma once
#include "BulletsBase.h"

//�Q
class VortexBullets : public BulletsBase
{
public:
	//�o���ʒu�̂݊O���@���a�E�_���[�W�E�X�s�[�h�͓����Őݒ�
	VortexBullets(T_LOCATION location, float speed, int angle);

	virtual void UpDate() override;           //�X�V
	virtual void Draw() override;             //�`��
	virtual bool IsScreenOut() override;      //��ʊO/��

private:

};

