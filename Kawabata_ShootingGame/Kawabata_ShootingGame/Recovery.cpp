#include"DxLib.h"
#include "Recovery.h"

//�R���X�g���N�^
Recovery::Recovery(T_LOCATION location)                                        
	:ItemBase(location, 12.0f, E_ITEM_TYPE::Heal, T_LOCATION{ 0,3 }), volume(20)//�񕜗�20
{
	image = LoadGraph("images/recovery.png");
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
	//�摜�Ȃ�
	if (image == 0)
	{
		DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 255));
	}
	else
	{
		DrawRotaGraphF(GetLocation().x, GetLocation().y, 1, 0, image, TRUE);
	}
}
