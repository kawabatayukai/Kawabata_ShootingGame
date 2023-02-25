#pragma once
#include "AbstractScene.h"

//�^�C�g��
class TitleScene : public AbstractScene
{
public:
	TitleScene();

	~TitleScene();           //�f�X�g���N�^

	void Update() override;            //�X�V

	void Draw() const override;        //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	int image_back;  //�摜
	int font;        //�t�H���g
};

