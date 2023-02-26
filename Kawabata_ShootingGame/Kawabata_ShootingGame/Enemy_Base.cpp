#include"DxLib.h"
#include"Enemy_Base.h"
#include"StraightBullets.h"
#include"VortexBullets.h"
#include"TakeAimBullets.h"
#include"HomingBullets.h"

//�R���X�g���N�^
Enemy_Base::Enemy_Base(T_LOCATION location, float radius, T_LOCATION speed, const char* pass)
	: CharaBase(location, radius, speed), moveinfo(), direction(Direction::LEFT)
{
	//Bullet * BULLETS_MAX���̃��������m��
	bullets = new BulletsBase * [BULLETS_MAX];    //�ő吔�@100  

	//������
	for (int i = 0; i < BULLETS_MAX; i++) bullets[i] = nullptr;


	//CSV�ǂݍ���
	if (pass != nullptr) InputCSV(pass);
}

//�X�V
void Enemy_Base::Update()
{

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

	//�e 
	int bulletCount;
	for (bulletCount = 0; bulletCount < BULLETS_MAX; bulletCount++)
	{
		//�z��̋�v�f�Ȃ甲����
		if (bullets[bulletCount] == nullptr) break;

		bullets[bulletCount]->Update();
		bullets[bulletCount]->SetTargetLocation(target);

		//��ʊO�ō폜����
		if (bullets[bulletCount]->IsScreenOut() == true)
		{
			DeleteBullet(bulletCount);   //�e���폜����

			bulletCount--;
		}
	}

	//attackpattern ��0�o�Ȃ��Ƃ��U������
	if (moveinfo[current].attackpattern != 0)
	{
		//�z��̋�v�f  �e�𔭎˂���
		if (bulletCount < BULLETS_MAX && bullets[bulletCount] == nullptr && frame_count % 30 == 0)
		{
			if (moveinfo[current].attackpattern == 1)          //�p�^�[��1
			{
				//���@�_��
				bullets[bulletCount]
					= new TakeAimBullets(GetLocation(), target, speed_TakeAim);
				
			}
			else if (moveinfo[current].attackpattern == 2)     //�p�^�[��2
			{
				//��]�e�𐶐�
				bullets[bulletCount] = 
					new VortexBullets(GetLocation(), speed_Vortex, (30 * shotNum));
				shotNum++;    //�J�E���^�[�𑝂₷
			}
			else if (moveinfo[current].attackpattern == 3)     //�p�^�[��2
			{
				//�z�[�~���O�e�𐶐�
				bullets[bulletCount] = 
					new HomingBullets(GetLocation(), speed_Homing);
			}
		}
	}
}

//�`��
void Enemy_Base::Draw()
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
		//0.5�{
		DrawRotaGraphF(GetLocation().x, GetLocation().y, 0.5, 0, image, TRUE);
	}

}

//�����������̏���
void Enemy_Base::Hit(int damage)
{
	//
	if (0 < damage)
	{
		hp -= damage;          //HP����
		if (0 > hp) hp = 0;    //HP��0��艺����Ȃ�
	}
}

//���̈ړ�
void Enemy_Base::Move()
{
    //���݂̈ʒu
	T_LOCATION nextLoacation = GetLocation();

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
				direction = Direction::RIGHT;

				if ((GetLocation().x <= moveinfo[current].targetLocation.x) && (moveinfo[current].targetLocation.x <= nextLoacation.x))
				{
					nextLoacation.x = moveinfo[current].targetLocation.x;  //���B��A�ڕW�𒴂����ꍇ��~
				}
			}
			else
			{
				nextLoacation.x -= speed.x;  //������
				direction = Direction::LEFT;

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
bool Enemy_Base::CheckHp()
{
	bool ret = (hp <= 0);
	return ret;
}

//�v���C���[�̍��W���擾
void Enemy_Base::SetTargetLocation(T_LOCATION location)
{
	target = location;
}


//csv�t�@�C���ǂݍ���
void Enemy_Base::InputCSV(const char* pass)
{
	FILE* fp; /*FILE�^�\����*/
	errno_t error; /*fopen_s�̃G���[�m�F*/
	error = fopen_s(&fp, pass, "r");

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


//���˂���e�̃X�s�[�h���Z�b�g    (�Ώۂ̒e , �X�s�[�h)
void Enemy_Base::SetBulletsSpeed(Bullet_Type type, float speed)
{
	//�Ώۂ̒e
	switch (type)
	{
	case Bullet_Type::Straight:     //�X�g���[�g

		speed_Straight = speed;
		break;

	case Bullet_Type::Vortex:       //��]

		speed_Vortex = speed;
		break;   

	case Bullet_Type::TakeAim:      //���@�_��

		speed_TakeAim = speed;
		break;  

	case Bullet_Type::Homing:       //�z�[�~���O

		speed_Homing = speed;
		break;

	default:
		break;
	}

	return;
}