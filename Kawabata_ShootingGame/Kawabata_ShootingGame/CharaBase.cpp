#include "CharaBase.h"

//�R���X�g���N�^     �������q���X�g
CharaBase::CharaBase(T_LOCATION location, float radius,T_LOCATION speed) 
	: SphereCollider(location, radius),speed(speed),image(nullptr)
{

}
