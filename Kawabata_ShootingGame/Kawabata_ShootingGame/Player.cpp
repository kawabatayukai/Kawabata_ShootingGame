#include"DxLib.h"
#include "Player.h"
#include"StraightBullets.h"
#include"KeyManager.h"

//�R���X�g���N�^          �����ʒu      �@�@�@�@�@�@   radius        speed               
Player::Player(T_LOCATION location) : CharaBase(location, 10.0f, T_LOCATION{ 5,5 }), score(0), life(10)
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

	if (KeyManager::OnKeyPressed(KEY_INPUT_W)) newLoacation.y -= speed.y;
	if (KeyManager::OnKeyPressed(KEY_INPUT_S)) newLoacation.y += speed.y;
	if (KeyManager::OnKeyPressed(KEY_INPUT_A)) newLoacation.x -= speed.x;
	if (KeyManager::OnKeyPressed(KEY_INPUT_D)) newLoacation.x += speed.x;
	
	SetLocation(newLoacation);


	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		//�z��̋�v�f
		if (bullets[bulletCount] == nullptr) break;
		bullets[bulletCount]->UpDate();

		//��ʊO�ō폜����
		if (bullets[bulletCount]->IsScreenOut() == true)
		{
			DeleteBullet(bulletCount);   //�e���폜����
			bulletCount--;
		}
	}


	if (KeyManager::OnMousePressed(MOUSE_INPUT_LEFT))
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
	DrawCircle(static_cast<int>(GetLocation().x), static_cast<int>(GetLocation().y), static_cast<int>(GetRadius()), GetColor(255, 0, 0));


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
void Player::Hit(int damage)
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
