#pragma once
#include "AbstractScene.h"

//�^�C�g��
class TitleScene : public AbstractScene
{
public:
	virtual ~TitleScene() {};           //�f�X�g���N�^

	void Update() override;            //�X�V

	void Draw() const override;        //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX
};

