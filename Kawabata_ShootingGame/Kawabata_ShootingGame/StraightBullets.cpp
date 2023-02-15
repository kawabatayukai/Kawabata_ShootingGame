#include"DxLib.h"
#include "StraightBullets.h"

StraightBullets::StraightBullets(T_LOCATION location,T_LOCATION speed)
	:BulletsBase(location, 5.0f, 3, speed)    //������ɂ܂�����
{

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
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(0, 200, 0));
}

////��ʊO/��
//bool StraightBullets::IsScreenOut()
//{
//	//StraightBullets�͏�����ɒ��i�̂�
//	bool ret = ((GetLocation().y + GetRadius()) <= 0 || (GetLocation().y - GetRadius() >= 720));
//
//	//if ((GetLocation().y + GetRadius()) <= 0 || (GetLocation().y - GetRadius() >= 480)) return true;
//
//	return ret;
//}