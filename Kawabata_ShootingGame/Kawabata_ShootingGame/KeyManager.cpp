#include"DxLib.h"
#include "KeyManager.h"

char KeyManager::oldKey[256];     //�O��̓���
char KeyManager::nowKey[256];     //����̓���

int KeyManager::oldMouse;         //�O��̃}�E�X����
int KeyManager::nowMouse;         //����̃}�E�X����

//�X�V
void KeyManager::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldKey[i] = nowKey[i];  //�O�t���[���̓���
	}

	//���ׂẴL�[�̂̓��͏�Ԃ��擾
	if (GetHitKeyStateAll(nowKey) == -1) throw - 1;

	//�}�E�X�̓��͏�Ԃ��擾
	oldMouse = nowMouse;
	nowMouse = GetMouseInput();
}

//�������u��
bool KeyManager::OnKeyClicked(int key)
{
	//���t���[��������Ă��Ȃ�        �@�@�@�@�@�@�@
	bool ret = (nowKey[key] == 1) && (oldKey[key] != 1);   //������Ă��Ȃ� �� 0
	return ret;
}

//�������u��
bool KeyManager::OnKeyReleased(int key)
{
	//          ���͉�����Ă��Ȃ��@  �O�͉�����Ă���
	bool ret = (nowKey[key] != 1) && (oldKey[key] == 1);
	return ret;
}

//�����Ă����
bool KeyManager::OnKeyPressed(int key)
{
	//
	bool ret = (nowKey[key] == 1);
	return ret;
}



//�������u�� (�m�F����L�[)
bool KeyManager::OnMouseClicked(int key)
{
	//���t���[��������Ă��Ȃ�        �@�@�@�@�@�@�@
	bool ret = (nowMouse & key) && (~oldMouse & key);
	return ret;
}

//�������u��
bool KeyManager::OnMouseReleased(int key)
{
	//          ���͉�����Ă��Ȃ��@  �O�͉�����Ă���
	bool ret = (~nowMouse & key) && (oldMouse & key);
	return ret;
}

//�����Ă����
bool KeyManager::OnMousePressed(int key)
{
	bool ret = (nowMouse & key);
	return ret;
}