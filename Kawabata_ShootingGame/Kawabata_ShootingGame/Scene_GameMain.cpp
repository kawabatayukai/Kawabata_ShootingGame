#include"DxLib.h"
#include"Scene_GameMain.h"

//�R���X�g���N�^
GameMainScene::GameMainScene()
{
	T_LOCATION location = T_LOCATION{ 20,100 };

	//�I�u�W�F�N�g�𐶐��E�A�h���X�m�ہE�R���X�g���N�^�Ăяo��
	player = new Player(location);

	enemy = new Enemy * [10];   //10�C���̃��������m��
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
	enemy[0] = new Enemy(T_LOCATION{ 200,0 });
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
	BulletsBase** bullet = player->GetBullets();   //�������Ă���e���擾

	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)	break;       //nullptr�̗v�f����ɂ͗v�fż
		enemy[enemyCount]->UpDate();

		//�G�ƒe�̓����蔻��
		for (int bulletCount = 0; bulletCount < 30; bulletCount++)
		{
			if (bullet[bulletCount] == nullptr) break;   //nullptr�̗v�f����ɂ͗v�fż

			//SphereCollider���m�̓����蔻��
			if ( enemy[enemyCount]->HitSphere( bullet[bulletCount]) )
			{
				//�G�ɒe���q�b�g

				//�G�Ƀ_���[�W������
				enemy[enemyCount]-> Hit( bullet[bulletCount]->GetDamage() );

				//�e���폜
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//�G��HP <= 0 �폜����
				if (enemy[enemyCount]->CheckHp())
				{
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
				}

			}
		}

	}
}

//�`��i�@^ �� ^�j
void GameMainScene::Draw() const
{
	player->Draw();
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] == nullptr) break;
		enemy[i]->Draw();
	}
}

//�V�[���̕ύX
AbstractScene* GameMainScene::ChangeScene()
{
	//if(player->LifeCheck()==true) return dynamic_cast<AbstractScene*>(new TitleS)

	//�X�V�Ȃ�
	return this;
}