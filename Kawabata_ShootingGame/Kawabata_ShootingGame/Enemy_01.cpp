#include"DxLib.h"
#include"Enemy_01.h"

//�R���X�g���N�^
Enemy_01::Enemy_01(T_LOCATION location, T_LOCATION speed)
	: Enemy_Base(location, 25.0f, speed, "CSV/moveinfo1.csv")
{
	//�摜�ǂݍ���
	image = LoadGraph("images/golf.png");

	hp = 10;      //HP��ݒ�
	point = 20;   //���_��ݒ�
}