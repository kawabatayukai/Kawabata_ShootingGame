#pragma once
#include"AbstractScene.h"

//�Q�[�����C��
class GameMainScene : public AbstractScene
{
public:
	
	GameMainScene();              //�R���X�g���N�^
	
	virtual ~GameMainScene() {}   //�f�X�g���N�^     
	
	void Update() override;  //�X�V
	
	void Draw() const override;        //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX
};
