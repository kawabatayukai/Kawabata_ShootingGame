#include "CharaBase.h"

//コンストラクタ     初期化子リスト
CharaBase::CharaBase(T_LOCATION location, float radius,T_LOCATION speed) 
	: SphereCollider(location, radius),speed(speed),image(nullptr),bullets(nullptr)
{

}

//弾情報取得
BulletsBase** CharaBase::GetBullets() { return bullets; }

//指定された要素番号の弾を削除
void CharaBase::DeleteBullet(int bulletNum)
{
	delete bullets[bulletNum];   //削除
	bullets[bulletNum] = nullptr;//初期化

	//配列を前に詰める
	for (int i = bulletNum; i < (100 - 1); i++)
	{
		if (bullets[i + 1] == nullptr) break;
		bullets[i] = bullets[i + 1];
		bullets[i + 1] = nullptr;  
		
		//詰めた元を初期化
	}
}