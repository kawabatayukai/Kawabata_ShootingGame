#include"DxLib.h"
#include"Scene_GameMain.h"

//�R���X�g���N�^
GameMainScene::GameMainScene()
{
	T_LOCATION location = T_LOCATION{ 20,100 };

	//�I�u�W�F�N�g�𐶐��E�A�h���X�m�ہE�R���X�g���N�^�Ăяo��
	player = new Player(location);
}

//�f�X�g���N�^
GameMainScene::~GameMainScene()
{
	//delete player;
}

//�X�V
void GameMainScene::Update()
{
	//T_LOCATION location = T_LOCATION{ 100,100 };
	//Player test = Player(location);
	////test.Draw();

	/*if (test.HitSphere(player)) return;*/
	player->UpDate();
}

//�`��
void GameMainScene::Draw() const
{
	player->Draw();
}

//�V�[���̕ύX
AbstractScene* GameMainScene::ChangeScene()
{
	//if(player->LifeCheck()==true) return dynamic_cast<AbstractScene*>(new TitleS)

	//�X�V�Ȃ�
	return this;
}