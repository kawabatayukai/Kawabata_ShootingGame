#include"DxLib.h"
#include "Player.h"
#include"StraightBullets.h"
#include"VortexBullets.h"
#include"KeyManager.h"
#include"Recovery.h"

//#define _DEBUG_MODE_


//コンストラクタ          初期位置      　　　　　　   radius        speed               
Player::Player(T_LOCATION location) : CharaBase(location, 25.0f, T_LOCATION{ 5,5 }), score(0), life(_LIFE_INIT)
{
	//メモリを確保する Bullets** bullets 

	bullets = new BulletsBase * [100];    //最大数　30  

	//弾配列を初期化
	for (int i = 0; i < 100; i++) bullets[i] = nullptr;

	//画像読み込み
	image = LoadGraph("images/spray.png");
}

//更新
void Player::Update()
{
	//現在の位置
	T_LOCATION newLoacation = GetLocation();

	if (KeyManager::OnKeyPressed(KEY_INPUT_W)) newLoacation.y -= speed.y;
	if (KeyManager::OnKeyPressed(KEY_INPUT_S)) newLoacation.y += speed.y;
	if (KeyManager::OnKeyPressed(KEY_INPUT_A)) newLoacation.x -= speed.x;
	if (KeyManager::OnKeyPressed(KEY_INPUT_D)) newLoacation.x += speed.x;

	SetLocation(newLoacation);


	int bulletCount;
	for (bulletCount = 0; bulletCount < 100; bulletCount++)
	{
		//配列の空要素
		if (bullets[bulletCount] == nullptr) break;
		bullets[bulletCount]->Update();

		//画面外で削除する
		if (bullets[bulletCount]->IsScreenOut() == true)
		{
			DeleteBullet(bulletCount);   //弾を削除する
			bulletCount--;
		}
	}


	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		//配列の空要素
		if (bulletCount < 100 && bullets[bulletCount] == nullptr)
		{
			bullets[bulletCount] = new StraightBullets(GetLocation(), T_LOCATION{ 0,-5 });
			//bullets[bulletCount] = new VortexBullets(GetLocation(), 8.0f, (20 * shotNum), GetColor(255, 255, 0));
			shotNum++;
		}
	}
}

//描画
void Player::Draw()
{
	//Debug

#ifdef _DEBUG_MODE_

	DrawFormatString(10, 10, GetColor(255, 255, 255), "life : %d", life);

#endif

	//0.5倍で描画
	DrawRotaGraphF(GetLocation().x, GetLocation().y, 0.5, 0, image, TRUE);

	for (int bulletCount = 0; bulletCount < 100; bulletCount++)
	{
		//配列の空要素なら処理しない
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
}

//当たった時の処理
void Player::Hit(int damage)
{
	if (0 < damage)
	{
		life -= damage;          //HP減少
		if (0 > life) life = 0;    //HPは0より下がらない
	}
}

//アイテムの効果
void Player::Hit(ItemBase* item)
{
	//アイテムのタイプを識別
	switch (item->GetType())
	{
	case E_ITEM_TYPE::Heal:
	{
		//case文中で変数を作成する時は変数の寿命に配慮する
		Recovery* recovery = dynamic_cast<Recovery*>(item);  //Recovery型に変換
		life += recovery->GetVolume();                       //回復力をプラス
	}
	break;

	case E_ITEM_TYPE::PowerUp:
		break;

	default:
		break;
	}
}

//"life"を確認
bool Player::LifeCheck()
{
	bool ret = (life <= 0);
	return ret;
}

//life取得
int Player::GetLife() const
{
	return life;
}

//スコア取得
int Player::GetScore() const { return score; }

//スコア加算
void Player::AddScore(int score)
{
	if (score >= 0)  this->score += score;
}