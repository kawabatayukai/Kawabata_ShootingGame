#include"DxLib.h"
#include "StraightBullets.h"

StraightBullets::StraightBullets(T_LOCATION location,T_LOCATION speed)
	:BulletsBase(location, 5.0f, 10, speed)    //������ɂ܂�����
{
	//�摜�ǂݍ���
	image = LoadGraph("images/bullets1.png");
}

//�X�V
void StraightBullets::UpDate()
{
	T_LOCATION newlocation = GetLocation();    //���̍��W
	newlocation.y += speed.y;                  //���W��ύX
	newlocation.x += speed.x;
	SetLocation(newlocation);                  //�ύX�𔽉f
}

//�`��
void StraightBullets::Draw()
{
	//DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(0, 200, 0));
	DrawRotaGraphF(GetLocation().x, GetLocation().y, 1, 0, image, TRUE);
}
