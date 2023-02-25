#pragma once
#include"SphereCollider.h"
#include"BulletsBase.h"

//キャラの基底クラス
class CharaBase : public SphereCollider
{
public:
	CharaBase(T_LOCATION location, float radius, T_LOCATION speed);

	virtual void Update() = 0;    //更新
	virtual void Draw() = 0;      //描画
	virtual void Hit(int damage) = 0;       //当たった時の処理

	BulletsBase** GetBullets();             //弾配列取得

	void DeleteBullet(int bulletNum);       //指定された要素番号の弾を削除

protected:

	BulletsBase** bullets;        //ポインタ配列
	T_LOCATION speed;

private:


	
};

