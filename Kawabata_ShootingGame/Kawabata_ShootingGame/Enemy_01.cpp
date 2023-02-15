#include"DxLib.h"
#include"Enemy_01.h"

//コンストラクタ
Enemy_01::Enemy_01(T_LOCATION location, T_LOCATION speed)
	: Enemy_Base(location, 25.0f, speed, "CSV/moveinfo1.csv")
{
	//画像読み込み
	image = LoadGraph("images/golf.png");

	hp = 10;      //HPを設定
	point = 20;   //得点を設定
}