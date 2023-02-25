#include "TakeAimBullets.h"
#include"DxLib.h"
#include<math.h>

//�o���ʒu�A�v���C���[�̍��W�A�X�s�[�h
TakeAimBullets::TakeAimBullets(T_LOCATION location, T_LOCATION p_location, float speed)
	:BulletsBase(location, 5.0f, 5, T_LOCATION{0,0})
{
	//�p�x�����߂�
	float rad = GetRadian(location, p_location);

	//�X�s�[�h�����߂�
	this->speed.x = cosf(rad) * speed;
	this->speed.y = sinf(rad) * speed;

	//�摜�ǂݍ���
	image = LoadGraph("images/bullets3.png");
}

//�X�V
void TakeAimBullets::UpDate()
{
	T_LOCATION newlocation = GetLocation();    //���̍��W
	newlocation.y += speed.y;                  //���W��ύX
	newlocation.x += speed.x;
	SetLocation(newlocation);                  //�ύX�𔽉f
}

//�`��
void TakeAimBullets::Draw()
{
	//DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 200, 0));
	DrawRotaGraphF(GetLocation().x, GetLocation().y, 1, 0, image, TRUE);
}

//�������W�ƖڕW���W�Ƃ̊p�x�����߂�
float TakeAimBullets::GetRadian(T_LOCATION self, T_LOCATION target)
{
	float w = target.x - self.x;     //�����W�̍����icos�Ɓj
	float h = target.y - self.y;     //�����W�̍����isin�Ɓj

	//�t���ڂ̎�l�����߂�
	return atan2f(h, w);
}