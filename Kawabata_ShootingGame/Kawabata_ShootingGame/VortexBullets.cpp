#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>

#include "VortexBullets.h"

VortexBullets::VortexBullets(T_LOCATION location, float speed, int angle, unsigned int color)
	: BulletsBase(location, 6.0f, 5, T_LOCATION{ 0,0 }), color(color)
{
	int deg = angle % 360;
	double rad = (M_PI / 180) * deg;   //�p�x�P�̎����l��360�x�@

	//0���Z(n/0)�����
	float x = static_cast<float>((abs(deg) == 90 || abs(deg) == 270) ? 0 : cos(rad)); //����cos
	float y = static_cast<float>(sin(rad));                                           //�c��sin

	//(sin+cos)=1   �c�Ɖ��ɐi�ޔ䗦 sin�Ecos��
	this->speed = T_LOCATION{ (speed * x),(speed * y) };

	//�摜�ǂݍ���
	image = LoadGraph("images/bullets4.png");
}

//�X�V
void VortexBullets::Update()
{
	T_LOCATION newlocation = GetLocation();    //���̍��W


	newlocation.y += speed.y;                  //���W��ύX
	newlocation.x += speed.x;
	SetLocation(newlocation);                  //�ύX�𔽉f
}

//�`��
void VortexBullets::Draw()
{
	//DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), color);
	DrawRotaGraphF(GetLocation().x, GetLocation().y, 1, 0, image, TRUE);
}
