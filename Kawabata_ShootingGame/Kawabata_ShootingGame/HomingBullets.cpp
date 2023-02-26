#include"HomingBullets.h"
#include"DxLib.h"

#define _USE_MATH_DEFINES
#include<math.h>

#define HOMING_TIME 100        //�ǐՎ���

//�R���X�g���N�^
HomingBullets::HomingBullets(T_LOCATION location, float speed)
	:BulletsBase(location, 6.0f, 5, T_LOCATION{ speed,speed })
{
	angle = M_PI / 2;   //�����̊p�x

	//�摜�ǂݍ���
	image = LoadGraph("images/bullets2.png");
}

//�X�V
void HomingBullets::Update()
{
	//���݂̍��W
	T_LOCATION nowlocation = GetLocation();

	//�ǐՎ��ԓ��@�@�@���ԊO�Œ��߂�
	if (time_counter < HOMING_TIME)
	{
		//���ݐi��ł������
		double now_x = cos(angle);    //����
		double now_y = sin(angle);    //����

		//�{���i�ނׂ�����
		double nxt_x = static_cast<double>(target.x) - nowlocation.x;    //����
		double nxt_y = static_cast<double>(target.y) - nowlocation.y;    //����



		double radius = 8;            //�ړ����a

		//�O�ς𗘗p���������^�[�Q�b�g���Ɍ�����
		if (((nxt_x * now_y) - (nxt_y * now_x)) < 0.0)
		{
			angle += M_PI / 180 * radius;
		}
		else
		{
			angle -= M_PI / 180 * radius;
		}

		time_counter++;                                   //�ǐՎ��ԃJ�E���g
	}

	nowlocation.x += static_cast<float>(cos(angle)) * speed.x;      //cos(�p�x)�@�ł����̈ړ��ʂ��v�Z
	nowlocation.y += static_cast<float>(sin(angle)) * speed.y;      //sin(�p�x)�@�ł����̈ړ��ʂ��v�Z

	//���W���Z�b�g
	SetLocation(nowlocation);
}

//�`��
void HomingBullets::Draw() 
{
	DrawRotaGraphF(GetLocation().x, GetLocation().y, 1, 0, image, TRUE);
}