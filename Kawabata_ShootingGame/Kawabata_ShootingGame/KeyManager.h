#pragma once

class KeyManager
{
public:
	static void Update();

	//キーボード
	static bool OnKeyClicked(int key);       //押した瞬間 (確認するキー)
	static bool OnKeyReleased(int key);      //離した瞬間
	static bool OnKeyPressed(int key);       //押している間

	//マウス
	static bool OnMouseClicked(int key);     //押した瞬間 (確認するキー)
	static bool OnMouseReleased(int key);    //離した瞬間
	static bool OnMousePressed(int key);     //押している間

private:
	//privateにコンストラクタ→アクセスできない（オブジェクトが作れない）
	KeyManager() = default;

private:
	static char oldKey[256];     //前回の入力
	static char nowKey[256];     //今回の入力

	static int oldMouse;         //前回のマウス入力
	static int nowMouse;         //今回のマウス入力

};

