#include"DxLib.h"
#include "Player.h"

//�R���X�g���N�^          �����ʒu      �@�@�@�@�@�@   radius        speed               
Player::Player(T_LOCATION location) : CharaBase(location, 10.0f, T_LOCATION{ 2,2 }), score(0), life(10)
{

}

//�X�V
void Player::UpDate()
{
	//���݂̈ʒu
	T_LOCATION newLoacation = GetLocation();

	newLoacation.x += 1;
	SetLocation(newLoacation);
}

//�`��
void Player::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 0));
}

//�����������̏���
void Player::Hit()
{

}

//"life"���m�F
bool Player::LifeCheck()
{
	bool ret = (life <= 0);
	return ret;
}

//�X�R�A�擾
int Player::GetScore() const { return score; }
