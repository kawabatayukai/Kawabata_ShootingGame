#pragma once
#include "AbstractScene.h"

//タイトル
class TitleScene : public AbstractScene
{
public:
	virtual ~TitleScene() {};           //デストラクタ

	void Update() override;            //更新

	void Draw() const override;        //描画

	AbstractScene* ChangeScene() override; //シーンの変更
};

