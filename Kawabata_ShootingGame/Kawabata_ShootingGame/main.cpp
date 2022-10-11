#include"DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetMainWindowText("Shooting");             //タイトルを設定
    ChangeWindowMode(TRUE);                //ウィンドウモードで起動
    //SetGraphMode(1280, 720, 32);           //ウィンドウサイズを設定
    if (DxLib_Init() == -1) return -1;     //DXライブラリの初期化処理
    SetDrawScreen(DX_SCREEN_BACK);         //描画先画面を裏にする

    while (ProcessMessage() == 0)
    {
        // 画面の初期化 
        ClearDrawScreen();

        DrawString(0, 0, "Test", 0xffffff);

        //裏画面の内容を表画面に反映
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}