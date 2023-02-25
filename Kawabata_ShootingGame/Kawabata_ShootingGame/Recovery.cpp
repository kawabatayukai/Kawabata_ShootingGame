#include"DxLib.h"
#include "Recovery.h"

//コンストラクタ
Recovery::Recovery(T_LOCATION location)                                        
	:ItemBase(location, 12.0f, E_ITEM_TYPE::Heal, T_LOCATION{ 0,3 }), volume(20)//回復量20
{
	image = LoadGraph("images/recovery.png");
}

//更新
void Recovery::UpDate()
{
	//現在の位置
	T_LOCATION newLoacation = GetLocation();

	newLoacation.y += speed.y;
	SetLocation(newLoacation);
}

//描画
void Recovery::Draw() const
{
	//画像なし
	if (image == 0)
	{
		DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 255));
	}
	else
	{
		DrawRotaGraphF(GetLocation().x, GetLocation().y, 1, 0, image, TRUE);
	}
}
