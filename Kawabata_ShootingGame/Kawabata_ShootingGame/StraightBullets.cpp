#include"DxLib.h"
#include "StraightBullets.h"

StraightBullets::StraightBullets(T_LOCATION location)
	:BulletsBase(location, 5.0f, 3, T_LOCATION{ 0,5 })    //������ɂ܂�����
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
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(0, 200, 0));
}

//��ʊO/��
bool StraightBullets::IsScreenOut()
{
	//StraightBullets�͏�����ɒ��i�̂�
	bool ret = ((GetLocation().y + GetRadius()) <= 0);

	return ret;
}