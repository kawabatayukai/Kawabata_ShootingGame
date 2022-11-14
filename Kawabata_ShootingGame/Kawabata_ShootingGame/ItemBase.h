#pragma once
#include"SphereCollider.h"
#include"E_ITEM_TYPE.h"

class ItemBase : public SphereCollider
{
public:
	ItemBase(T_LOCATION location, float radius, E_ITEM_TYPE type, T_LOCATION speed);

	virtual void UpDate() = 0;
	virtual void Draw()const = 0 ;
	E_ITEM_TYPE GetType() const;     //タイプ取得

protected:
	T_LOCATION speed;         //スピード

private:
	E_ITEM_TYPE type;         //タイプ
};

