#pragma once
#include"AbstractScene.h"
#include"Player.h"
#include"Enemy.h"
#include"ItemBase.h"

//�Q�[�����C��
class GameMainScene : public AbstractScene
{
public:
	
	GameMainScene();              //�R���X�g���N�^
	
	~GameMainScene();             //�f�X�g���N�^     
	
	void Update() override;  //�X�V
	
	void Draw() const override;        //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	Player* player;
	Enemy** enemy;
	ItemBase** items;
};
