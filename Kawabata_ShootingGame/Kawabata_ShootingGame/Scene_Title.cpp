#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_Title.h"
#include"Scene_GameMain.h"

//�R���X�g���N�^
TitleScene::TitleScene()
{
	SetFontSize(50);
}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
	SetFontSize(10);
}

//�X�V
void TitleScene::Update()
{

}

//�`��
void TitleScene::Draw() const
{
	//
	DrawString(100, 70, "�^�C�g��", 0xffffff);
	DrawString(100, 170, "�X�y�[�X�L�[�ŃX�^�[�g", 0xffffff);
}

//�V�[���̕ύX
AbstractScene* TitleScene::ChangeScene()
{
	//�X�y�[�X�L�[�ŃV�[���؂�ւ�
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE) == true)
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
	}

	//�X�V�Ȃ�
	return this;
}
