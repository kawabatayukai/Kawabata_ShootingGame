#pragma once
#include "AbstractScene.h"

//�^�C�g��
class GameClearScene : public AbstractScene
{
public:
	GameClearScene();
	~GameClearScene();           //�f�X�g���N�^

	void Update() override;            //�X�V

	void Draw() const override;        //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX
};
