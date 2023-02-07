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

int next[3] = { 1,2,1 }; //�ڕW���W�̓Y��
int frame_count = 0;     //�t���[�����J�E���g

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

	InputCSV();
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

	
	//�p�^�[�������ꂽ����     0 : ����/ 1 : �����Ȃ� 
	switch (moveinfo[current].pattern)
	{
	case 0:   //����
		Move();
		break;

	case 1:   //�����Ă��Ȃ�

		frame_count++;                         //�t���[�����J�E���g

		//�p�^�[���Ō��߂�ꂽ�҂����Ԃ��o��
		if (moveinfo[current].waitTime <= frame_count)
		{
			frame_count = 0;                   //�J�E���g�����Z�b�g
			current = moveinfo[current].next;  //���̃p�^�[����
		}

		break;

	default:
		break;
	}

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

	//attackpattern ��0�o�Ȃ��Ƃ��U������
	if (moveinfo[current].attackpattern != 0)
	{
		//�z��̋�v�f  �e�𔭎˂���
		if (bulletCount < BULLETS_MAX && bullets[bulletCount] == nullptr)
		{
			if (moveinfo[current].attackpattern == 1)          //�p�^�[��1
			{
				//�܂������z�𐶐�
				bullets[bulletCount]
					= new StraightBullets(GetLocation(), T_LOCATION{ 0.0f,8.0f});
			}
			else if (moveinfo[current].attackpattern == 2)     //�p�^�[��2
			{
				//�@�@��]�z�𐶐�
				bullets[bulletCount] = new VortexBullets(GetLocation(), 8.0f, (20 * shotNum));
				shotNum++;    //�J�E���^�[�𑝂₷
			}
		}
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

	DrawFormatString(0, 50, 0xffffff, "No. : %d", current);
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
	////���݂̈ʒu
	//T_LOCATION nextLoacation = GetLocation();

	//speed = { 5.0f,5.0f };

	////�ړI���W�Ɗ��S��v
	//if ((nextLoacation.y == locations[current].y) && (nextLoacation.x == locations[current].x))
	//{
	//	current = next[current];
	//}
	//else
	//{
	//	//�����W���s��v
	//	if (nextLoacation.y != locations[current].y)
	//	{
	//		//�ڕW���W�̂ق����傫���i�ڕW�͉��j
	//		if (nextLoacation.y < locations[current].y)
	//		{
	//			nextLoacation.y += speed.y;  //������

	//			if ((GetLocation().y <= locations[current].y) && (locations[current].y <= nextLoacation.y))
	//			{
	//				nextLoacation.y = locations[current].y;  //���B��A�ڕW�𒴂����ꍇ��~
	//			}
	//		}
	//		else
	//		{
	//			nextLoacation.y -= speed.y;  //�����
	//			if ((nextLoacation.y <= locations[current].y) && (locations[current].y <= GetLocation().y))
	//			{
	//				nextLoacation.y = locations[current].y;  //���B��A�ڕW�𒴂����ꍇ��~
	//			}
	//		}
	//	}

	//	//�����W���s��v
	//	if (nextLoacation.x != locations[current].x)
	//	{
	//		//�ڕW���W�̂ق����傫���i�ڕW�͉E�j
	//		if (nextLoacation.x < locations[current].x)
	//		{
	//			nextLoacation.x += speed.x;  //�E����
	//			if ((GetLocation().x <= locations[current].x) && (locations[current].x <= nextLoacation.x))
	//			{
	//				nextLoacation.x = locations[current].x;  //���B��A�ڕW�𒴂����ꍇ��~
	//			}
	//		}
	//		else
	//		{
	//			nextLoacation.x -= speed.x;
	//			if ((nextLoacation.x <= locations[current].x) && (locations[current].x <= GetLocation().x))
	//			{
	//				nextLoacation.x = locations[current].x;  //���B��A�ڕW�𒴂����ꍇ��~
	//			}
	//		}
	//	}
	//}



		//���݂̈ʒu
	T_LOCATION nextLoacation = GetLocation();

	speed = { 5.0f,5.0f };

	//�ړI���W�Ɗ��S��v
	if ((nextLoacation.y == moveinfo[current].targetLocation.y) && (nextLoacation.x == moveinfo[current].targetLocation.x))
	{
		current = moveinfo[current].next;   //���S��v�Ŏ��̃p�^�[����
	}
	else
	{
		//�����W���s��v
		if (nextLoacation.y != moveinfo[current].targetLocation.y)
		{
			//�ڕW���W�̂ق����傫���i�ڕW�͉��j
			if (nextLoacation.y < moveinfo[current].targetLocation.y)
			{
				nextLoacation.y += speed.y;  //������

				if ((GetLocation().y <= moveinfo[current].targetLocation.y) && (moveinfo[current].targetLocation.y <= nextLoacation.y))
				{
					nextLoacation.y = moveinfo[current].targetLocation.y;  //���B��A�ڕW�𒴂����ꍇ��~
				}
			}
			else
			{
				nextLoacation.y -= speed.y;  //�����
				if ((nextLoacation.y <= moveinfo[current].targetLocation.y) && (moveinfo[current].targetLocation.y <= GetLocation().y))
				{
					nextLoacation.y = moveinfo[current].targetLocation.y;  //���B��A�ڕW�𒴂����ꍇ��~
				}
			}
		}

		//�����W���s��v
		if (nextLoacation.x != moveinfo[current].targetLocation.x)
		{
			//�ڕW���W�̂ق����傫���i�ڕW�͉E�j
			if (nextLoacation.x < moveinfo[current].targetLocation.x)
			{
				nextLoacation.x += speed.x;  //�E����
				if ((GetLocation().x <= moveinfo[current].targetLocation.x) && (moveinfo[current].targetLocation.x <= nextLoacation.x))
				{
					nextLoacation.x = moveinfo[current].targetLocation.x;  //���B��A�ڕW�𒴂����ꍇ��~
				}
			}
			else
			{
				nextLoacation.x -= speed.x;
				if ((nextLoacation.x <= moveinfo[current].targetLocation.x) && (moveinfo[current].targetLocation.x <= GetLocation().x))
				{
					nextLoacation.x = moveinfo[current].targetLocation.x;  //���B��A�ڕW�𒴂����ꍇ��~
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

//csv�t�@�C���ǂݍ���
void Enemy::InputCSV()
{
	FILE* fp; /*FILE�^�\����*/
	errno_t error; /*fopen_s�̃G���[�m�F*/
	error = fopen_s(&fp, "CSV/moveinfo.csv", "r");

	/*(�u���C�N�|�C���g��t����)�t�@�C���̊J�e�X�g*/
	if (error != 0)
	{
		return; //�G���[����
	}
	else //�t�@�C�����J����
	{
		char line[100]; //�s
		/*fgets(line, ������, fp)*/
		//fgets(line, 100, fp);
		//
		for (int i = 0; fgets(line, 100, fp) != NULL; i++)
		{


			sscanf_s(
				line, //�s
				"%d,%f,%f,%d,%d,%d",       //(int, float, float, int, int, int)
				&moveinfo[i].pattern,          /*���@�E�p�^�[��*/
				&moveinfo[i].targetLocation.x, /*�ړI�n.X���W*/
				&moveinfo[i].targetLocation.y, /*�ړI�n.Y���W*/
				&moveinfo[i].next,             /*����(�z��)����*/
				&moveinfo[i].waitTime,    /*(�҂��Ȃ�)����*/
				&moveinfo[i].attackpattern     /*�U�����@*/
			);

			
		}
		return;
	}
	fclose(fp); /*�t�@�C�������*/
}