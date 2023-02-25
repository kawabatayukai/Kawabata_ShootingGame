#pragma once
#include "CharaBase.h"

//life初期値
#define _LIFE_INIT  200

//プレイヤークラス
class Player : public CharaBase
{
public:
	Player(T_LOCATION location);                //コンストラクタ

	void Update() override;  //更新
	void Draw() override;    //描画
	void Hit(int damage) override;     //当たった時の処理
	void Hit(class ItemBase* item);    //アイテムの効果
	
	bool LifeCheck();                  //"life"を確認
	int GetLife() const;               //life取得
	int GetScore() const;              //スコア取得
	void AddScore(int score);          //スコア加算

private:
	int score;
	int life;
	int shotNum = 0;

	int image;
};

