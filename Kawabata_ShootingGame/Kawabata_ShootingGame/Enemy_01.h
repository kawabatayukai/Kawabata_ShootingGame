#pragma once
#include"Enemy_Base.h"

class Enemy_01 : public Enemy_Base
{
public:
	//�R���X�g���N�^
	Enemy_01(T_LOCATION location, T_LOCATION speed = { 5.0f,5.0f });
};

