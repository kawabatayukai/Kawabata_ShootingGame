#include"DxLib.h"
#include"Scene_GameMain.h"
#include"Recovery.h"

//�R���X�g���N�^
GameMainScene::GameMainScene()
{
	T_LOCATION location = T_LOCATION{ 20,100 };

	//�I�u�W�F�N�g�𐶐��E�A�h���X�m�ہE�R���X�g���N�^�Ăяo��
	player = new Player(location);

	//10�C���̃��������m��
	enemy = new Enemy * [10];
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
	//enemy[0] = new Enemy(T_LOCATION{ 600,300 });
	enemy[0] = new Enemy();

	//Item 10���̃��������m��
	items = new ItemBase * [10];
	for (int i = 0; i < 10; i++) items[i] = nullptr;
}

//�f�X�g���N�^
GameMainScene::~GameMainScene()
{
	//delete player;
}

//�X�V
void GameMainScene::Update()
{
	player->UpDate();

	int enemyCount;
	
	//Item�X�V
	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr) break;
		items[i]->UpDate();
	}

	//Enemy�ƃv���C���[�̒e�̓����蔻��
	BulletsBase** bullet = player->GetBullets();   //�������Ă���e���擾
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		//Enemy�X�V
		if (enemy[enemyCount] == nullptr)	break;       //nullptr�̗v�f����ɂ͗v�fż
		enemy[enemyCount]->UpDate();

		//�G�ƒe�̓����蔻��
		for (int bulletCount = 0; bulletCount < 100; bulletCount++)
		{
			if (bullet[bulletCount] == nullptr) break;   //nullptr�̗v�f����ɂ͗v�fż

			//SphereCollider���m�̓����蔻��
			if (enemy[enemyCount]->HitSphere(bullet[bulletCount]))
			{
				//�G�ɒe���q�b�g

				//�G�Ƀ_���[�W������
				enemy[enemyCount]->Hit(bullet[bulletCount]->GetDamage());

				//�e���폜
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//�G��HP <= 0 �폜����
				if (enemy[enemyCount]->CheckHp() == true)
				{
					for (int i = 0; i < 10; i++)
					{
						if (items[i] == nullptr)
						{
							items[i] = new Recovery(enemy[enemyCount]->GetLocation());
							break;
						}
					}

					//�X�R�A���Z
					player->AddScore(enemy[enemyCount]->GetPoint());

					delete enemy[enemyCount];
					enemy[enemyCount] = nullptr;

					//�l�߂�
					for (int i = enemyCount; i < (10 - 1); i++)
					{
						if (enemy[i + 1] == nullptr) break;
						enemy[i] = enemy[i + 1];
						enemy[i + 1] = nullptr;                //�l�߂�����������
					}
					enemyCount--;
					break;
				}
			}
		}
	}

	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr) break;
		bullet= enemy[enemyCount]->GetBullets();    //�G�̕ێ�����e

		for (int bulletCount = 0; bulletCount < 100; bulletCount++)
		{
			if (bullet[bulletCount] == nullptr) break;   //nullptr�̗v�f����ɂ͗v�fż

			//SphereCollider���m�̓����蔻��
			if (player->HitSphere(bullet[bulletCount]))
			{
				//�v���C���[�Ƀ_���[�W��^����
				player->Hit(bullet[bulletCount]->GetDamage());

				//�e���폜
				enemy[enemyCount]->DeleteBullet(bulletCount);
				bulletCount--;
				break;
			}
		}
	}

	//Item��Player�̓����蔻��
	for (int itemCount = 0; itemCount < 10; itemCount++)
	{
		if (items[itemCount] == nullptr) break;   //nullptr�̗v�f����ɂ͗v�fż

		if (items[itemCount]->HitSphere(player) == true)
		{
			//�A�C�e���̌��ʂ𔽉f
			player->Hit(items[itemCount]);

			delete items[itemCount];
			items[itemCount] = nullptr;

			//�z����l�߂�
			for (int i = itemCount; i < (10 - 1); i++)
			{
				if (items[itemCount] == nullptr) break;
				items[i] = items[i + 1];
				items[i + 1] = nullptr;                //�l�߂�����������
			}
			itemCount--;
		}
	}

}

//�`��
void GameMainScene::Draw() const
{
	player->Draw();
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] == nullptr) break;
		enemy[i]->Draw();
	}

	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr) break;
		items[i]->Draw();
	}

	DrawFormatString(0, 0, 0xffffff, "%f %f", enemy[0]->GetLocation().x, enemy[0]->GetLocation().y);
}

//�V�[���̕ύX
AbstractScene* GameMainScene::ChangeScene()
{
	//if(player->LifeCheck()==true) return dynamic_cast<AbstractScene*>(new TitleS)

	//�X�V�Ȃ�
	return this;
}