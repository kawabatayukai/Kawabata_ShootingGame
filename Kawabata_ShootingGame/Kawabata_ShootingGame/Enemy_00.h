#pragma once
#include"Enemy_Base.h"

class Enemy_00 : public Enemy_Base
{
public:
	//コンストラクタ
	Enemy_00(T_LOCATION location, T_LOCATION speed = { 5.0f,5.0f });

	void Draw() override;     //描画　再定義
};
