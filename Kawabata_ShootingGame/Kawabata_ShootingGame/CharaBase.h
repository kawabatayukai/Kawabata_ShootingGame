#pragma once
#include"SphereCollider.h"

//キャラの基底クラス
class CharaBase : public SphereCollider
{
public:
	CharaBase(T_LOCATION location, float radius, T_LOCATION speed);

	virtual void UpDate() = 0;    //更新
	virtual void Draw() = 0;      //描画
	virtual void Hit() = 0;       //当たった時の処理

	//GetBullets();

protected:
	int* image;

private:
	//bullets ポインタ配列
	T_LOCATION speed;
};

