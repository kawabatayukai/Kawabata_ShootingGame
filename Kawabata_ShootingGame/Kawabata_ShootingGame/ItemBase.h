#pragma once
#include"SphereCollider.h"
#include"E_ITEM_TYPE.h"

class ItemBase : public SphereCollider
{
public:
	ItemBase(T_LOCATION location, float radius, E_ITEM_TYPE type, T_LOCATION speed);

	virtual void UpDate() = 0;
	virtual void Draw()const = 0 ;
	E_ITEM_TYPE GetType() const;     //�^�C�v�擾

protected:
	T_LOCATION speed;         //�X�s�[�h

private:
	E_ITEM_TYPE type;         //�^�C�v
};

