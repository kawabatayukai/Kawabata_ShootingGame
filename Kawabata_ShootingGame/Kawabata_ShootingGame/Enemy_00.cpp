#include"DxLib.h"
#include"Enemy_00.h"

//�R���X�g���N�^
Enemy_00::Enemy_00(T_LOCATION location, T_LOCATION speed)
	: Enemy_Base(location, 25.0f, speed, "CSV/moveinfo.csv")
{
	//�摜�ǂݍ���
	//image = LoadGraph("images/golf.png");

	
	hp = 10;      //HP��ݒ�
	point = 10;   //���_��ݒ�
}