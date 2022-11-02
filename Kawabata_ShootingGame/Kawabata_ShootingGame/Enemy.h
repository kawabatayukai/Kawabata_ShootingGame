#pragma once
#include "CharaBase.h"

class Enemy : public CharaBase
{
public:
	Enemy(T_LOCATION location);

	virtual void UpDate() override;  //
	virtual void Draw()   override;  //
	virtual void Hit(int damage)    override;  //

	bool CheckHp();           //Hpをチェック
	int GetPoint() { return point; }           //ポイント取得

private:
	int hp;
	int point;
};

