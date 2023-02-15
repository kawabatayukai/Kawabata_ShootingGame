#pragma once
#include"Enemy_Base.h"

class Enemy_01 : public Enemy_Base
{
public:
	//コンストラクタ
	Enemy_01(T_LOCATION location, T_LOCATION speed = { 5.0f,5.0f });
};

