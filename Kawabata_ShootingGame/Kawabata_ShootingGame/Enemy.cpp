#include"DxLib.h"
#include "Enemy.h"
#include"StraightBullets.h"
#include"VortexBullets.h"

#define BULLETS_MAX 100

//�ړ��ڕW
T_LOCATION target[4] =
{
	{640,-10},
	{640,150},
	{100,150},
	{1180,150}
};

//�ړ��ڕW���W
T_LOCATION locations[3] =
{
	{640,150},
	{1200.4f,150},
	{80.2f,150},
};

//�ړ����@�G�̓���
struct MoveInfo
{
	T_LOCATION targetLocation;   //�ڕW
	int pattern;                 //����/�����Ȃ�
	int next;                    //
	int waitTime;                //
	int attackpattern;           //�U��/�U�����Ȃ�  0:�U�����Ȃ��@0<n:�U��
};

//10�p�^�[��
MoveInfo moveinfo[10] =
{
	{    640,150, 0, 1,  0, 0},
	{1200.4f,150, 0, 2,  0, 0},
	{      0,  0, 1, 3,180, 1},   //�����Ȃ� 3�b�� �U��
	{  80.2f,150, 0, 4,  0, 2},   //�����@�@�@�@�@ �U��
	{      0,  0, 1, 5,180, 1},   //�����Ȃ� 3�b�� �U��
	{1200.4f,150, 0, 2,  0, 1},   
};

int next[3] = { 1,2,1 }; //�ڕW���W�̓Y��
int current = 0;         //���݁Z�Ԗڂ̍��W

//�R���X�g���N�^
Enemy::Enemy(T_LOCATION location)
	: CharaBase(location, 20.0f, T_LOCATION{ 0,0.0 }), hp(10), point(10), shotNum(0),nowlocation(0)
{
	//���������m�ۂ��� Bullets** bullets 
	bullets = new BulletsBase * [BULLETS_MAX];    //�ő吔�@30  

	for (int i = 0; i < BULLETS_MAX; i++)
	{
		bullets[i] = nullptr;
	}
}

//�X�V
void Enemy::UpDate()
{
	////���݂̈ʒu
	//T_LOCATION newLoacation = GetLocation();

	//speed = { 3.0f,3.0f };
	//if (nowlocation < 2) speed = { 2.0f,2.0f };

	////���Ɉړ�����
	//if (target[nowlocation].x != newLoacation.x) speed.y = 0.0f;

	//if (target[nowlocation].x > newLoacation.x) speed.x = speed.x;
	//else if (target[nowlocation].x < newLoacation.x) speed.x = -speed.x;
	//else
	//{
	//	speed.x = 0.0f;

	//	if (target[nowlocation].y > newLoacation.y) speed.y = speed.y;
	//	else if (target[nowlocation].y < newLoacation.y) speed.y = -speed.y;
	//	else
	//	{
	//		speed.y = 0.0f;
	//		nowlocation++;

	//		if (nowlocation > 3) nowlocation = 2;
	//	}
	//}

	Move();

	//newLoacation.x += speed.x;
	//newLoacation.y += speed.y;
	//SetLocation(newLoacation);         //�ړ�

	//�e 
	int bulletCount;
	for (bulletCount = 0; bulletCount < BULLETS_MAX; bulletCount++)
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
	if (bulletCount < BULLETS_MAX && bullets[bulletCount] == nullptr)
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
	for (int bulletCount = 0; bulletCount < BULLETS_MAX; bulletCount++)
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

//���̈ړ�
void Enemy::Move()
{
	//���݂̈ʒu
	T_LOCATION nextLoacation = GetLocation();

	speed = { 3.0f,3.0f };

	//�ړI���W�Ɗ��S��v
	if ((nextLoacation.y == locations[current].y) && (nextLoacation.x == locations[current].x))
	{
		current = next[current];
	}
	else
	{
		//�����W���s��v
		if (nextLoacation.y != locations[current].y)
		{
			//�ڕW���W�̂ق����傫���i�ڕW�͉��j
			if (nextLoacation.y < locations[current].y)
			{
				nextLoacation.y += speed.y;  //������

				if ((GetLocation().y <= locations[current].y) && (locations[current].y <= nextLoacation.y))
				{
					nextLoacation.y = locations[current].y;  //���B��A�ڕW�𒴂����ꍇ��~
				}
			}
			else
			{
				nextLoacation.y -= speed.y;  //�����
				if ((nextLoacation.y <= locations[current].y) && (locations[current].y <= GetLocation().y))
				{
					nextLoacation.y = locations[current].y;  //���B��A�ڕW�𒴂����ꍇ��~
				}
			}
		}

		//�����W���s��v
		if (nextLoacation.x != locations[current].x)
		{
			//�ڕW���W�̂ق����傫���i�ڕW�͉E�j
			if (nextLoacation.x < locations[current].x)
			{
				nextLoacation.x += speed.x;  //�E����
				if ((GetLocation().x <= locations[current].x) && (locations[current].x <= nextLoacation.x))
				{
					nextLoacation.x = locations[current].x;  //���B��A�ڕW�𒴂����ꍇ��~
				}
			}
			else
			{
				nextLoacation.x -= speed.x;
				if ((nextLoacation.x <= locations[current].x) && (locations[current].x <= GetLocation().x))
				{
					nextLoacation.x = locations[current].x;  //���B��A�ڕW�𒴂����ꍇ��~
				}
			}
		}
	}

	SetLocation(nextLoacation);
}

//Hp�`�F�b�N
bool Enemy::CheckHp()
{
	bool ret = (hp <= 0);
	return ret;
}