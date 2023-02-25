#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>

#include "VortexBullets.h"

VortexBullets::VortexBullets(T_LOCATION location, float speed, int angle, unsigned int color)
	: BulletsBase(location, 5.0f, 5, T_LOCATION{ 0,0 }), color(color)
{
	//speed.x = cosf(angle* 3.14f / 180);
	//speed.y = sinf(angle* 3.14f / 180);

	int deg = angle % 360;
	double rad = (M_PI / 180) * deg;   //�p�x�P�̎����l��360�x�@

	//0���Z(n/0)�����
	float x = static_cast<float>((abs(deg) == 90 || abs(deg) == 270) ? 0 : cos(rad)); //����cos
	float y = static_cast<float>(sin(rad));                                           //�c��sin

	//(sin+cos)=1   �c�Ɖ��ɐi�ޔ䗦 sin�Ecos��
	this->speed = T_LOCATION{ (speed * x),(speed * y) };
}

//�X�V
void VortexBullets::UpDate()
{
	T_LOCATION newlocation = GetLocation();    //���̍��W


	newlocation.y += speed.y;                  //���W��ύX
	newlocation.x += speed.x;
	SetLocation(newlocation);                  //�ύX�𔽉f
}

//�`��
void VortexBullets::Draw()
{
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), color);
}

////��ʊO/��
//bool VortexBullets::IsScreenOut()
//{
//	
//	//StraightBullets�͏�����ɒ��i�̂�
//	bool ret = ((GetLocation().y + GetRadius()) <= 0 || (GetLocation().y - GetRadius() >= 720)|| (GetLocation().x + GetRadius()) <= 0 || (GetLocation().x - GetRadius()) >= 1280);
//	return ret;
//
//	//ret = ((GetLocation().x + GetRadius()) <= 0 || (GetLocation().x - GetRadius()) >= 1280);
//	//return ret;
//}
