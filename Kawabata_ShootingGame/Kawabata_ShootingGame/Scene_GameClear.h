#pragma once
#include "AbstractScene.h"

//�^�C�g��
class GameClearScene : public AbstractScene
{
public:
	//�R���X�g���N�^�i�X�R�A�����炤�j
	GameClearScene(int score = 0);
	~GameClearScene();           //�f�X�g���N�^

	void Update() override;            //�X�V

	void Draw() const override;        //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	int last_score;  //�\������X�R�A

	int image_back;  //�摜
	int font;        //�t�H���g
	int font1;
};

