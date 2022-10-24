#include"DxLib.h"
#include "KeyManager.h"

char KeyManager::oldKey[256];     //前回の入力
char KeyManager::nowKey[256];     //今回の入力

int KeyManager::oldMouse;         //前回のマウス入力
int KeyManager::nowMouse;         //今回のマウス入力

//更新
void KeyManager::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldKey[i] = nowKey[i];  //前フレームの入力
	}

	//すべてのキーのの入力状態を取得
	if (GetHitKeyStateAll(nowKey) == -1) throw - 1;

	//マウスの入力状態を取得
	oldMouse = nowMouse;
	nowMouse = GetMouseInput();
}

//押した瞬間
bool KeyManager::OnKeyClicked(int key)
{
	//毎フレーム押されていない        　　　　　　　
	bool ret = (nowKey[key] == 1) && (oldKey[key] != 1);   //押されていない → 0
	return ret;
}

//離した瞬間
bool KeyManager::OnKeyReleased(int key)
{
	//          今は押されていない　  前は押されていた
	bool ret = (nowKey[key] != 1) && (oldKey[key] == 1);
	return ret;
}

//押している間
bool KeyManager::OnKeyPressed(int key)
{
	//
	bool ret = (nowKey[key] == 1);
	return ret;
}



//押した瞬間 (確認するキー)
bool KeyManager::OnMouseClicked(int key)
{
	//毎フレーム押されていない        　　　　　　　
	bool ret = (nowMouse & key) && (~oldMouse & key);
	return ret;
}

//離した瞬間
bool KeyManager::OnMouseReleased(int key)
{
	//          今は押されていない　  前は押されていた
	bool ret = (~nowMouse & key) && (oldMouse & key);
	return ret;
}

//押している間
bool KeyManager::OnMousePressed(int key)
{
	bool ret = (nowMouse & key);
	return ret;
}