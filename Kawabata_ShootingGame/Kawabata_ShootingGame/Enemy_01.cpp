#include"DxLib.h"
#include"Enemy_01.h"
#include"TakeAimBullets.h"
#include"VortexBullets.h"

//�R���X�g���N�^
Enemy_01::Enemy_01(T_LOCATION location, T_LOCATION speed)
	: Enemy_Base(location, 25.0f, speed, "CSV/moveinfo1.csv")
{
	//�摜�ǂݍ���
	image = LoadGraph("images/ka.png");

	hp = 10;      //HP��ݒ�
	point = 20;   //���_��ݒ�

	//�e�̃X�s�[�h��ݒ�
	SetBulletsSpeed(Bullet_Type::TakeAim, 7.0f);
	SetBulletsSpeed(Bullet_Type::Vortex, 6.0f);
	SetBulletsSpeed(Bullet_Type::Homing, 5.0f);
}


//�`��
void Enemy_01::Draw()
{
	//�e
	for (int bulletCount = 0; bulletCount < BULLETS_MAX; bulletCount++)
	{
		//�z��̋�v�f
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}

	//�摜���Ȃ��Ƃ�
	if (image == 0)
	{
		DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 255));
	}
	else
	{
		//���摜��0.5�{

		//�����ɂ���Ĕ��]/���]���Ȃ�
		bool reverse = direction == Direction::RIGHT ? true : false;
		DrawRotaGraphF(GetLocation().x, GetLocation().y, 0.5, 0, image, TRUE, reverse);
	}
}