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
	font = CreateFontToHandle(NULL, 90, 20, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
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
	//�J�[�\���ړ�
	if (KeyManager::OnKeyClicked(KEY_INPUT_S)) menu_num++;
	if (menu_num > 1) menu_num = 0;
	if (KeyManager::OnKeyClicked(KEY_INPUT_W)) menu_num--;
	if (menu_num < 0) menu_num = 1;
}

//�`��
void TitleScene::Draw() const
{
	//�w�i
	DrawGraph(0, 0, image_back, TRUE);

	//�J�[�\��
	DrawCircle(420, (440 + (menu_num * 100)), 30, 0x00ff00, TRUE);

	DrawStringToHandle(300, 150, "Insect Fight", 0x00ff00, font, 0x000000);
	DrawStringToHandle(500, 400, "START", 0x00ff00, font, 0x000000);
	DrawStringToHandle(500, 500, " END ", 0x00ff00, font, 0x000000);
}

//�V�[���̕ύX
AbstractScene* TitleScene::ChangeScene()
{
	//�X�y�[�X�L�[�ŃV�[���؂�ւ�
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE) == true)
	{
		switch (menu_num)
		{
		case 0:   //�Q�[�����C��
			return dynamic_cast<AbstractScene*> (new GameMainScene());
			break;

		case 1:   //�I��
			return nullptr;

		default:
			break;
		}

		
	}

	//�X�V�Ȃ�
	return this;
}
