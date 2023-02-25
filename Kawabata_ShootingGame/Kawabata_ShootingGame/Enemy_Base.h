#pragma once
#include"CharaBase.h"

#define BULLETS_MAX 100

//移動情報　敵の動き
struct MoveInfo
{
	int pattern;                 //動く/動かない
	T_LOCATION targetLocation;   //目標
	int next;                    //次はパターン〇番目
	int waitTime;                //
	int attackpattern;           //攻撃/攻撃しない  0:攻撃しない　0<n:攻撃
};

//向き
enum class Direction
{
	LEFT,      //左
	RIGHT      //右
};

//敵キャラの基底クラス
class Enemy_Base : public CharaBase
{
public:
	//コンストラクタ    座標、半径、スピード、csvのパスを設定
	Enemy_Base(T_LOCATION location, float radius, T_LOCATION speed, const char* pass = nullptr);

	void Update() override;          //更新
	virtual void Draw()   override;  //描画
	void Hit(int damage)  override;  //当たり（ダメージ）

	void Move();                     //一定の移動
	bool CheckHp();                  //Hpをチェック
	int GetPoint() { return point; } //ポイント取得

	//プレイヤーの座標をもらう
	void SetTargetLocation(T_LOCATION location);

	//csvファイル読み込み
	void InputCSV(const char* pass);          

private:

	int shotNum = 0;       //発射した数
	int frame_count = 0;   //フレームをカウント

	MoveInfo moveinfo[10]; //移動パターン
	int current = 0;       //現在〇番目の座標
	T_LOCATION target = { 0,0 };

protected:
	int hp = 0;            //HP
	int point = 0;         //得点

	int image = 0; //画像

	Direction direction;   //向き
};
