#include "SceneManager.h"

//Update()�E�E�����o�ϐ��̒l��ύX
AbstractScene* SceneManager::Update()
{
    //���݃V�[���̃A�b�v�f�[�g�����s
    AbstractScene* p = mScene->Update();

    //UpDate�ł�������V�[�������݂̃V�[���ƈقȂ�ꍇ
    //���݂̃V�[�����폜���A�V���ȃV�[���ɐ؂�ւ���
    if (p != mScene)
    {
        delete mScene;
        mScene = p;
    }

    //�V���ȃV�[����Ԃ�
    return p;
}


//���݂̃V�[���� Draw(�`����s���֐�)�݂̂����s
void SceneManager::Draw() const
{
    //const �̓����o�ϐ��̕ύX������
    mScene->Draw();
}