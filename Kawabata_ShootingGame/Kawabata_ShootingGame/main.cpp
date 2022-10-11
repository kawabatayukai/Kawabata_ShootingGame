#include"DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetMainWindowText("Shooting");             //�^�C�g����ݒ�
    ChangeWindowMode(TRUE);                //�E�B���h�E���[�h�ŋN��
    //SetGraphMode(1280, 720, 32);           //�E�B���h�E�T�C�Y��ݒ�
    if (DxLib_Init() == -1) return -1;     //DX���C�u�����̏���������
    SetDrawScreen(DX_SCREEN_BACK);         //�`����ʂ𗠂ɂ���

    while (ProcessMessage() == 0)
    {
        // ��ʂ̏����� 
        ClearDrawScreen();

        DrawString(0, 0, "Test", 0xffffff);

        //����ʂ̓��e��\��ʂɔ��f
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}