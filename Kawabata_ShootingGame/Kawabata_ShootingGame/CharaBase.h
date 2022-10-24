#pragma once
#include"SphereCollider.h"
#include"BulletsBase.h"

//キャラの基底クラス
class CharaBase : public SphereCollider
{
public:
	CharaBase(T_LOCATION location, float radius, T_LOCATION speed);

	virtual void UpDate() = 0;    //更新
	virtual void Draw() = 0;      //描画
	virtual void Hit() = 0;       //当たった時の処理

	BulletsBase** GetBullets();   //

protected:
	int* image;
	BulletsBase** bullets;        //ポインタ配列

private:


	T_LOCATION speed;
};

