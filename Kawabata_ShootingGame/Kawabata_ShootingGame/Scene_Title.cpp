#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_Title.h"
#include"Scene_GameMain.h"

//�R���X�g���N�^
TitleScene::TitleScene()
{
	//�摜�ǂݍ���
	image_back = LoadGraph("images/back.png");

	//�t�H���g���쐬
	font = CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
	//�t�H���g�f�[�^���폜
	DeleteFontToHandle(font);
}

//�X�V
void TitleScene::Update()
{

}

//�`��
void TitleScene::Draw() const
{
	//�w�i
	DrawGraph(0, 0, image_back, TRUE);

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
