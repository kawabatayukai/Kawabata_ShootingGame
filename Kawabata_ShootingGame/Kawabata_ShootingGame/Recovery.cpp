#include"DxLib.h"
#include "Recovery.h"

//コンストラクタ
Recovery::Recovery(T_LOCATION location)                                        
	:ItemBase(location, 5.0f, E_ITEM_TYPE::Heal, T_LOCATION{ 0,5 }), volume(20)//回復量20
{

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
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 255));
}
