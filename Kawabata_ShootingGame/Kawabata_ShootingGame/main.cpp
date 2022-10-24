#include"DxLib.h"
#include"SceneManager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetMainWindowText("Shooting");             //タイトルを設定
    ChangeWindowMode(TRUE);                //ウィンドウモードで起動
    //SetGraphMode(1280, 720, 32);           //ウィンドウサイズを設定
    if (DxLib_Init() == -1) return -1;     //DXライブラリの初期化処理
    SetDrawScreen(DX_SCREEN_BACK);         //描画先画面を裏にする


    //シーンマネージャー     　　　　　　　　　　　　　　　ﾀｲﾄﾙを設定
    SceneManager sceneMng( dynamic_cast<AbstractScene*>(new GameMainScene()) );

    while (ProcessMessage() == 0)
    {
        // 画面の初期化 
        ClearDrawScreen();

        sceneMng.Update();     //更新
        sceneMng.Draw();       //描画

        //シーンの変更   ENDの場合　nullptr
        if (sceneMng.ChangeScene() == nullptr)
        {
            DxLib_End();  //DxLib終了処理
            return 0;     
        }

        //裏画面の内容を表画面に反映
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}