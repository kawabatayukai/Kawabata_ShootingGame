#pragma once

class KeyManager
{
public:
	static void Update();

	//�L�[�{�[�h
	static bool OnKeyClicked(int key);       //�������u�� (�m�F����L�[)
	static bool OnKeyReleased(int key);      //�������u��
	static bool OnKeyPressed(int key);       //�����Ă����

	//�}�E�X
	static bool OnMouseClicked(int key);     //�������u�� (�m�F����L�[)
	static bool OnMouseReleased(int key);    //�������u��
	static bool OnMousePressed(int key);     //�����Ă����

private:
	//private�ɃR���X�g���N�^���A�N�Z�X�ł��Ȃ��i�I�u�W�F�N�g�����Ȃ��j
	KeyManager() = default;

private:
	static char oldKey[256];     //�O��̓���
	static char nowKey[256];     //����̓���

	static int oldMouse;         //�O��̃}�E�X����
	static int nowMouse;         //����̃}�E�X����

};

