#pragma once
#include "CharaBase.h"

//プレイヤークラス
class Player : public CharaBase
{
public:
	Player(T_LOCATION location);                //コンストラクタ

	void UpDate() override;  //更新
	void Draw() override;    //描画
	void Hit() override;     //当たった時の処理
	
	bool LifeCheck();        //"life"を確認
	int GetScore() const;    //スコア取得

private:
	int score;
	int life;
};

