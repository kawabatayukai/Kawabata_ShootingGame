#pragma once
#include"Enemy_Base.h"

class Enemy_00 : public Enemy_Base
{
public:
	//�R���X�g���N�^
	Enemy_00(T_LOCATION location, T_LOCATION speed = { 5.0f,5.0f });

	void Draw() override;     //�`��@�Ē�`
};
