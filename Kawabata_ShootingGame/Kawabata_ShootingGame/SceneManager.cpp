#include "SceneManager.h"

//Update()・・メンバ変数の値を変更
AbstractScene* SceneManager::Update()
{
    //現在シーンのアップデートを実行
    AbstractScene* p = mScene->Update();

    //UpDateでもらったシーンが現在のシーンと異なる場合
    //現在のシーンを削除し、新たなシーンに切り替える
    if (p != mScene)
    {
        delete mScene;
        mScene = p;
    }

    //新たなシーンを返す
    return p;
}


//現在のシーンの Draw(描画を行う関数)のみを実行
void SceneManager::Draw() const
{
    //const はメンバ変数の変更を拒否
    mScene->Draw();
}