#pragma once
#include "AbstractScene.h"

//�Q�[���I�[�o�[
class GameOverScene : public AbstractScene
{
public:
	GameOverScene();
	~GameOverScene();           //�f�X�g���N�^

	void Update() override;            //�X�V

	void Draw() const override;        //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	int image_back;  //�摜
	int font;        //�t�H���g
};

