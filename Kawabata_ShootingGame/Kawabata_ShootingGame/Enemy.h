#pragma once
#include "CharaBase.h"

class Enemy : public CharaBase
{
public:
	Enemy(T_LOCATION location);

	virtual void UpDate() override;  //
	virtual void Draw()   override;  //
	virtual void Hit(int damage)    override;  //

	bool CheckHp();           //Hp���`�F�b�N
	int GetPoint() { return point; }           //�|�C���g�擾

private:
	int hp;
	int point;
};

