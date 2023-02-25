#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_GameMain.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"Recovery.h"
#include"Enemy_01.h"
#include"Enemy_00.h"



//�R���X�g���N�^
GameMainScene::GameMainScene()
{

	//�I�u�W�F�N�g�𐶐��E�������m�ہE�R���X�g���N�^�Ăяo��
	player = new Player(T_LOCATION{ P_INIT_X,P_INIT_Y });

	//Enemy10�C���̃��������m��
	enemy = new Enemy_Base * [10];    
	
	for (int i = 0; i < 10; i++) enemy[i] = nullptr;    //������

	//�������W�E�X�s�[�h�i�f�t�H���g��5�j��ݒ�
	enemy[0] = new Enemy_00(T_LOCATION{ 640,0 },T_LOCATION{ 4.f,4.f });       //Enemy00�𐶐�
	enemy[1] = new Enemy_00(T_LOCATION{ -10,730 }, T_LOCATION{ 4.f,4.f });       //Enemy01�𐶐�

	//Item 10���̃��������m��
	items = new ItemBase * [10];
	for (int i = 0; i < 10; i++) items[i] = nullptr;


	//�摜�ǂݍ���
	image_back = LoadGraph("images/Main_back.png");

	//�t�H���g���쐬
	font = CreateFontToHandle(NULL, 25, 7, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	//Life�o�[������
	ui_box_y = BAR_BOTTOM - BAR_MAX;
}
//�f�X�g���N�^
GameMainScene::~GameMainScene()
{
	//�t�H���g�f�[�^���폜
	DeleteFontToHandle(font);
}

//�X�V
void GameMainScene::Update()
{
	player->Update();

	//�v���C���[�ړ��͈͂̐���
	float x = player->GetLocation().x;
	float y = player->GetLocation().y;
	float r = player->GetRadius();

	//���[
	if ((x - r) < 0)           player->SetLocation(T_LOCATION{ r,y });   
	//�E�[
	if ((x + r) > PLAY_AREA_W) player->SetLocation(T_LOCATION{ (PLAY_AREA_W - r),y });   
	//��[
	if ((y - r) < 0)           player->SetLocation(T_LOCATION{ x,r });
	//���[
	if ((y + r) > 720)         player->SetLocation(T_LOCATION{ x,(720 - r) });

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
		enemy[enemyCount]->Update();

		//�v���C���[�̍��W���擾
		enemy[enemyCount]->SetTargetLocation(player->GetLocation());  

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

	UI_Update();
}

//�`��
void GameMainScene::Draw() const
{
	//�w�i
	DrawGraph(0, 0, image_back, FALSE);

	//player
	player->Draw();

	//Enemy
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] == nullptr) break;
		enemy[i]->Draw();
	}
	
	//Item
	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr) break;
		items[i]->Draw();
	}

	
	if (enemy[0] == nullptr)
	{
		DrawFormatStringToHandle(300, 100, 0xffffff, font,"STAGE %d CLEAR", stage);
		DrawStringToHandle(300, 130, "Press Space Key", 0xffffff, font);
	}

	UI_Draw();
}

//�V�[���̕ύX
AbstractScene* GameMainScene::ChangeScene()
{
	//�v���C���[���S�ŃV�[���؂�ւ�
	if (player->LifeCheck() == true) return dynamic_cast<AbstractScene*>(new GameOverScene());


	//Enemy�S�łŎ��̃X�e�[�W
	if (enemy[0] == nullptr && stage < 4)
	{
		//������
		if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE))
		{
			Stage_Init(stage);
			stage++;
		}
		
	}

	if (enemy[0] == nullptr && stage == 4)
		return dynamic_cast<AbstractScene*>(new GameClearScene());


	//�X�V�Ȃ�
	return this;
}

//�X�e�[�W�ύX
void GameMainScene::Stage_Init(int now_stage)
{
	//�G��������
	for (int i = 0; i < 10; i++) enemy[i] = nullptr;    

	//�G�𐶐��inow_stage : ���݂̃X�e�[�W�j
	switch (now_stage)
	{
	case 1:               //�X�e�[�W1�̎��A�X�e�[�W2��
		enemy[0] = new Enemy_00(T_LOCATION{ 640,0 });
		enemy[1] = new Enemy_00(T_LOCATION{ 320,0 });
		enemy[2] = new Enemy_01(T_LOCATION{ 640,0 });
		enemy[3] = new Enemy_01(T_LOCATION{ 320,0 });
		break;

	case 2:
		enemy[0] = new Enemy_00(T_LOCATION{ 640,0 });
		enemy[1] = new Enemy_00(T_LOCATION{ 320,0 });
		enemy[2] = new Enemy_01(T_LOCATION{ 640,0 });
		enemy[3] = new Enemy_01(T_LOCATION{ 320,0 });
		enemy[4] = new Enemy_00(T_LOCATION{ 330,0 });
		enemy[5] = new Enemy_00(T_LOCATION{ 560,0 });
		enemy[6] = new Enemy_01(T_LOCATION{ 140,0 });
		enemy[7] = new Enemy_01(T_LOCATION{ 80,0 });
		break;

	default:
		break;
	}




	//�v���C���[�̍��W��������
	player->SetLocation(T_LOCATION{ P_INIT_X,P_INIT_Y });
}

//UI�X�V
void GameMainScene::UI_Update()
{
	ui_box_y = BAR_BOTTOM - static_cast<float>(player->GetLife() * 2.5);
	if (ui_box_y < (BAR_BOTTOM - BAR_MAX)) ui_box_y = BAR_BOTTOM - BAR_MAX;
}


//UI�`��
void GameMainScene::UI_Draw() const
{
	//UI�`��G���A
	DrawBox(PLAY_AREA_W, 0, 1280, 720, GetColor(0, 255, 0), TRUE);
	DrawBox(PLAY_AREA_W + 10 , 10, 1280 - 10, 720 - 10, 0x696969, TRUE);

	//�v���C���[Life�o�[
	DrawBox(1140, (BAR_BOTTOM - BAR_MAX - 10), (1130 + 110), BAR_BOTTOM + 10, 0xffffff, TRUE);
	DrawBox(1150, (BAR_BOTTOM - BAR_MAX), (1150 + 80), BAR_BOTTOM, 0x000000, TRUE);
	DrawBoxAA(1150, (ui_box_y), (1150 + 80), BAR_BOTTOM, 0xff69b4, TRUE);
	
	//"Life"  
	DrawFormatStringToHandle(1120, 130, 0xffffff, font, "LIFE : %d", player->GetLife(), 0xffff00);
	//"stage"
	DrawFormatStringToHandle(1120, 80, 0xffffff, font, "Stage : %d", stage);
}