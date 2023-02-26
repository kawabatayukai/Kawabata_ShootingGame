#include"DxLib.h"
#include "Player.h"
#include"StraightBullets.h"
#include"VortexBullets.h"
#include"KeyManager.h"
#include"Recovery.h"

//#define _DEBUG_MODE_


//�R���X�g���N�^          �����ʒu      �@�@�@�@�@�@   radius        speed               
Player::Player(T_LOCATION location) : CharaBase(location, 25.0f, T_LOCATION{ 5,5 }), score(0), life(_LIFE_INIT)
{
	//���������m�ۂ��� Bullets** bullets 

	bullets = new BulletsBase * [100];    //�ő吔�@30  

	//�e�z���������
	for (int i = 0; i < 100; i++) bullets[i] = nullptr;

	//�摜�ǂݍ���
	image = LoadGraph("images/spray.png");
}

//�X�V
void Player::Update()
{
	//���݂̈ʒu
	T_LOCATION newLoacation = GetLocation();

	if (KeyManager::OnKeyPressed(KEY_INPUT_W)) newLoacation.y -= speed.y;
	if (KeyManager::OnKeyPressed(KEY_INPUT_S)) newLoacation.y += speed.y;
	if (KeyManager::OnKeyPressed(KEY_INPUT_A)) newLoacation.x -= speed.x;
	if (KeyManager::OnKeyPressed(KEY_INPUT_D)) newLoacation.x += speed.x;

	SetLocation(newLoacation);


	int bulletCount;
	for (bulletCount = 0; bulletCount < 100; bulletCount++)
	{
		//�z��̋�v�f
		if (bullets[bulletCount] == nullptr) break;
		bullets[bulletCount]->Update();

		//��ʊO�ō폜����
		if (bullets[bulletCount]->IsScreenOut() == true)
		{
			DeleteBullet(bulletCount);   //�e���폜����
			bulletCount--;
		}
	}


	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		//�z��̋�v�f
		if (bulletCount < 100 && bullets[bulletCount] == nullptr)
		{
			bullets[bulletCount] = new StraightBullets(GetLocation(), T_LOCATION{ 0,-5 });
			//bullets[bulletCount] = new VortexBullets(GetLocation(), 8.0f, (20 * shotNum), GetColor(255, 255, 0));
			shotNum++;
		}
	}
}

//�`��
void Player::Draw()
{
	//Debug

#ifdef _DEBUG_MODE_

	DrawFormatString(10, 10, GetColor(255, 255, 255), "life : %d", life);

#endif

	//0.5�{�ŕ`��
	DrawRotaGraphF(GetLocation().x, GetLocation().y, 0.5, 0, image, TRUE);

	for (int bulletCount = 0; bulletCount < 100; bulletCount++)
	{
		//�z��̋�v�f�Ȃ珈�����Ȃ�
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
	if (0 < damage)
	{
		life -= damage;          //HP����
		if (0 > life) life = 0;    //HP��0��艺����Ȃ�
	}
}

//�A�C�e���̌���
void Player::Hit(ItemBase* item)
{
	//�A�C�e���̃^�C�v������
	switch (item->GetType())
	{
	case E_ITEM_TYPE::Heal:
	{
		//case�����ŕϐ����쐬���鎞�͕ϐ��̎����ɔz������
		Recovery* recovery = dynamic_cast<Recovery*>(item);  //Recovery�^�ɕϊ�
		life += recovery->GetVolume();                       //�񕜗͂��v���X
	}
	break;

	case E_ITEM_TYPE::PowerUp:
		break;

	default:
		break;
	}
}

//"life"���m�F
bool Player::LifeCheck()
{
	bool ret = (life <= 0);
	return ret;
}

//life�擾
int Player::GetLife() const
{
	return life;
}

//�X�R�A�擾
int Player::GetScore() const { return score; }

//�X�R�A���Z
void Player::AddScore(int score)
{
	if (score >= 0)  this->score += score;
}