#include"DxLib.h"
#include "Player.h"
#include"StraightBullets.h"

//�R���X�g���N�^          �����ʒu      �@�@�@�@�@�@   radius        speed               
Player::Player(T_LOCATION location) : CharaBase(location, 10.0f, T_LOCATION{ 2,2 }), score(0), life(10)
{
	//���������m�ۂ��� Bullets** bullets 
	
	bullets = new BulletsBase * [30];    //�ő吔�@30  

	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}
}

//�X�V
void Player::UpDate()
{
	//���݂̈ʒu
	T_LOCATION newLoacation = GetLocation();

	newLoacation.x += 1;
	SetLocation(newLoacation);


	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//�z��̋�v�f
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->UpDate();
	}


	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//�z��̋�v�f
		if (bulletCount < 30 && bullets[bulletCount] == nullptr)
		{
			bullets[bulletCount] = new StraightBullets(GetLocation());
		}

	}


}

//�`��
void Player::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 0));


	for (int bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//�z��̋�v�f
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
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
