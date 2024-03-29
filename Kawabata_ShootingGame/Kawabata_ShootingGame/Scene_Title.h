#pragma once
#include "AbstractScene.h"

//タイトル
class TitleScene : public AbstractScene
{
public:
	TitleScene();

	~TitleScene();           //デストラクタ

	void Update() override;            //更新

	void Draw() const override;        //描画

	AbstractScene* ChangeScene() override; //シーンの変更

private:
	int menu_num = 0;//セレクトNo.

	int image_back;  //画像
	int font;        //フォント
};

