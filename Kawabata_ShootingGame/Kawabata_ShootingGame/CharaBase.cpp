#include "CharaBase.h"

//�R���X�g���N�^     �������q���X�g
CharaBase::CharaBase(T_LOCATION location, float radius,T_LOCATION speed) 
	: SphereCollider(location, radius),speed(speed),image(nullptr),bullets(nullptr)
{

}

//�e���擾
BulletsBase** CharaBase::GetBullets() { return bullets; }

//�w�肳�ꂽ�v�f�ԍ��̒e���폜
void CharaBase::DeleteBullet(int bulletNum)
{
	delete bullets[bulletNum];   //�폜
	bullets[bulletNum] = nullptr;//������

	//�z���O�ɋl�߂�
	for (int i = bulletNum; i < (100 - 1); i++)
	{
		if (bullets[i + 1] == nullptr) break;
		bullets[i] = bullets[i + 1];
		bullets[i + 1] = nullptr;  
		
		//�l�߂�����������
	}
}