#pragma once
#include"AbstractScene.h"
#include"Player.h"
#include"Enemy_Base.h"
#include"ItemBase.h"

//�Q�[���v���C�̈�
#define PLAY_AREA_W 1100

//�v���C���[�������W
#define P_INIT_X    640.0f
#define P_INIT_Y    500.0f

//ui 
#define BAR_BOTTOM  680   //�v���C���[life�o�[�̉��[
#define BAR_MAX     500   //�o�[�̍ő咷

//�Q�[�����C��
class GameMainScene : public AbstractScene
{
public:
	
	GameMainScene();              //�R���X�g���N�^
	
	~GameMainScene();             //�f�X�g���N�^     
	
	void Update() override;                //�X�V
	void Draw() const override;            //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

	void Stage_Init(int now_stage);        //�X�e�[�W�ύX

	void UI_Update();                      //UI�X�V
	void UI_Draw() const;                  //UI�`��

private:
	Player* player;
	Enemy_Base** enemy;
	ItemBase** items;

	int stage = 1;    //�X�e�[�W�J�E���g�ϐ�

	int image_back;   //�w�i�摜
	int font;         //�t�H���g�f�[�^

	float ui_box_y;   //hp�o�[��y���W
};
