#include"DxLib.h"
#include "Enemy.h"
#include"StraightBullets.h"
#include"VortexBullets.h"

//�R���X�g���N�^
Enemy::Enemy(T_LOCATION location) : CharaBase(location, 20.0f, T_LOCATION{ 0,0.0 }), hp(10), point(10), shotNum(0)
{
	//���������m�ۂ��� Bullets** bullets 
	bullets = new BulletsBase * [30];    //�ő吔�@30  

	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}
}

//�X�V
void Enemy::UpDate()
{
	//���݂̈ʒu
	T_LOCATION newLoacation = GetLocation();
	newLoacation.y += speed.y;
	SetLocation(newLoacation);         //�ړ�

	//�e 
	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//�z��̋�v�f
		if (bullets[bulletCount] == nullptr) break;
		bullets[bulletCount]->UpDate();

		//��ʊO�ō폜����
		if (bullets[bulletCount]->IsScreenOut() == true)
		{
			DeleteBullet(bulletCount);   //�e���폜����
			//if (shotNum > 0) shotNum--;

			bulletCount--;
		}
	}

	//�z��̋�v�f
	if (bulletCount < 30 && bullets[bulletCount] == nullptr)
	{
		bullets[bulletCount] = new VortexBullets(GetLocation(), 3.0f, (20 * shotNum));
		shotNum++;
	}
}

//�`��
void Enemy::Draw()
{
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 255));
	
	//�e
	for (int bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//�z��̋�v�f
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
}

//�����������̏���
void Enemy::Hit(int damage)
{
	//
	if (0 < damage)
	{
		hp -= damage;          //HP����
		if (0 > hp) hp = 0;    //HP��0��艺����Ȃ�
	}
}

//Hp�`�F�b�N
bool Enemy::CheckHp()
{
	bool ret = (hp <= 0);
	return ret;
}