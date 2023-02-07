#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameOver.h"
#include"Scene_Title.h"

//�R���X�g���N�^
GameOverScene::GameOverScene()
{
	SetFontSize(50);
}

//�f�X�g���N�^
GameOverScene::~GameOverScene()
{
	SetFontSize(10);
}

//�X�V
void GameOverScene::Update()
{
	
}



//�`��
void GameOverScene::Draw() const
{
	//
	DrawString(100, 70, "Game Over", 0xffffff);
	DrawString(100, 170, "�X�y�[�X�L�[�Ń^�C�g����", 0xffffff);
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
