#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameClear.h"
#include"Scene_Title.h"

//�R���X�g���N�^
GameClearScene::GameClearScene()
{
	SetFontSize(50);
}

//�f�X�g���N�^
GameClearScene::~GameClearScene()
{
	SetFontSize(10);
}

//�X�V
void GameClearScene::Update()
{

}



//�`��
void GameClearScene::Draw() const
{
	//
	DrawString(100, 70, "Game Clear", 0xffffff);
	DrawString(100, 170, "�X�y�[�X�L�[�Ń^�C�g����", 0xffffff);
}

//�V�[���̕ύX
AbstractScene* GameClearScene::ChangeScene()
{
	//�X�y�[�X�L�[�ŃV�[���؂�ւ�
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE) == true)
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}

	//�X�V�Ȃ�
	return this;
}
