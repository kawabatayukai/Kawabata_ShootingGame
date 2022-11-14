#include"DxLib.h"
#include "Enemy.h"

//�R���X�g���N�^
Enemy::Enemy(T_LOCATION location) : CharaBase(location, 20.0f, T_LOCATION{ 0,0.5 }), hp(10), point(10)
{

}

//�X�V
void Enemy::UpDate()
{
	//���݂̈ʒu
	T_LOCATION newLoacation = GetLocation();

	newLoacation.y += speed.y;
	SetLocation(newLoacation);
}

//�`��
void Enemy::Draw()
{
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 255));
}

//�����������̏���
void Enemy::Hit(int damage)
{
	//
	if (0 < damage)
	{
		hp -= damage;          //HP����
		if (0 > hp) hp = 0;    //HP��0��艺����Ȃ�
	}
}

//Hp�`�F�b�N
bool Enemy::CheckHp()
{
	bool ret = (hp <= 0);
	return ret;
}