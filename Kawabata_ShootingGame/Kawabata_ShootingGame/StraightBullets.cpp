#include"DxLib.h"
#include "StraightBullets.h"

StraightBullets::StraightBullets(T_LOCATION location)
	:BulletsBase(location, 5.0f, 3, T_LOCATION{ 0,9 })    //������ɂ܂�����
{

}

//�X�V
void StraightBullets::UpDate()
{
	T_LOCATION newlocation = GetLocation();    //���̍��W
	newlocation.y -= speed.y;                  //���W��ύX

	SetLocation(newlocation);                  //�ύX�𔽉f
}

//�`��
void StraightBullets::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 0));
}