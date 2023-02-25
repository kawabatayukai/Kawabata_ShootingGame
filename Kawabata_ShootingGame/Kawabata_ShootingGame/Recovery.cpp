#include"DxLib.h"
#include "Recovery.h"

//�R���X�g���N�^
Recovery::Recovery(T_LOCATION location)                                        
	:ItemBase(location, 5.0f, E_ITEM_TYPE::Heal, T_LOCATION{ 0,5 }), volume(20)//�񕜗�20
{

}

//�X�V
void Recovery::UpDate()
{
	//���݂̈ʒu
	T_LOCATION newLoacation = GetLocation();

	newLoacation.y += speed.y;
	SetLocation(newLoacation);
}

//�`��
void Recovery::Draw() const
{
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 255));
}
