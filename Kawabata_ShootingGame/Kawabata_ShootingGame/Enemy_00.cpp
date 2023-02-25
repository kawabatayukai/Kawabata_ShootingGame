#include"DxLib.h"
#include"Enemy_00.h"

//�R���X�g���N�^
Enemy_00::Enemy_00(T_LOCATION location, T_LOCATION speed)
	: Enemy_Base(location, 20.0f, speed, "CSV/moveinfo.csv")
{
	//�摜�ǂݍ���
	image = LoadGraph("images/goki.png");
	
	hp = 10;      //HP��ݒ�
	point = 10;   //���_��ݒ�
}

//�`��
void Enemy_00::Draw()
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
		bool reverse = direction == Direction::LEFT ? true : false;
		DrawRotaGraphF(GetLocation().x, GetLocation().y, 0.7, 0, image, TRUE, reverse);
	}
}