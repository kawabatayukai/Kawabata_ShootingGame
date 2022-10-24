#include "CharaBase.h"

//コンストラクタ     初期化子リスト
CharaBase::CharaBase(T_LOCATION location, float radius,T_LOCATION speed) 
	: SphereCollider(location, radius),speed(speed),image(nullptr),bullets(nullptr)
{

}

//弾情報取得
BulletsBase** CharaBase::GetBullets() { return bullets; }