#include"DxLib.h"
#include"SceneManager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetMainWindowText("Shooting");             //�^�C�g����ݒ�
    ChangeWindowMode(TRUE);                //�E�B���h�E���[�h�ŋN��
    //SetGraphMode(1280, 720, 32);           //�E�B���h�E�T�C�Y��ݒ�
    if (DxLib_Init() == -1) return -1;     //DX���C�u�����̏���������
    SetDrawScreen(DX_SCREEN_BACK);         //�`����ʂ𗠂ɂ���


    //�V�[���}�l�[�W���[     �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���ق�ݒ�
    SceneManager sceneMng( dynamic_cast<AbstractScene*>(new GameMainScene()) );

    while (ProcessMessage() == 0)
    {
        // ��ʂ̏����� 
        ClearDrawScreen();

        sceneMng.Update();     //�X�V
        sceneMng.Draw();       //�`��

        //�V�[���̕ύX   END�̏ꍇ�@nullptr
        if (sceneMng.ChangeScene() == nullptr)
        {
            DxLib_End();  //DxLib�I������
            return 0;     
        }

        //����ʂ̓��e��\��ʂɔ��f
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}