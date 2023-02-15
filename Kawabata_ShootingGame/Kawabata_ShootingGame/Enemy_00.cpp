#include"DxLib.h"
#include"Enemy_00.h"

//コンストラクタ
Enemy_00::Enemy_00(T_LOCATION location, T_LOCATION speed)
	: Enemy_Base(location, 25.0f, speed, "CSV/moveinfo.csv")
{
	//画像読み込み
	//image = LoadGraph("images/golf.png");

	
	hp = 10;      //HPを設定
	point = 10;   //得点を設定
}