#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameOver.h"
#include"Scene_Title.h"

//�R���X�g���N�^
GameOverScene::GameOverScene()
{
	//�摜�ǂݍ���
	image_back = LoadGraph("images/back.png");

	//�t�H���g���쐬
	font = CreateFontToHandle(NULL, 150, 20, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2);
	font1 = CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

//�f�X�g���N�^
GameOverScene::~GameOverScene()
{
	//�t�H���g�f�[�^���폜
	DeleteFontToHandle(font);
	DeleteFontToHandle(font1);
}

//�X�V
void GameOverScene::Update()
{
	
}



//�`��
void GameOverScene::Draw() const
{
	//�w�i
	DrawGraph(0, 0, image_back, TRUE);

	DrawStringToHandle(280, 150, "Game Over", 0xffa500, font, 0x000000);
	DrawStringToHandle(380, 500, "Press Space To Title", 0xffa500, font1, 0x000000);
}

//�V�[���̕ύX
AbstractScene* GameOverScene::ChangeScene()
{
	//�X�y�[�X�L�[�ŃV�[���؂�ւ�
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE) == true)
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}

	//�X�V�Ȃ�
	return this;
}
