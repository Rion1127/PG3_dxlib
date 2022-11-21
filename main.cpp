#include "DxLib.h"
#include "SceneManager.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2A_�X�Y�L_���I��";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 400;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	SceneManager* sceneManager = SceneManager::GetInstance();

	int color_ = 0xffffff;

	const char* nowSceneName = "a";
	const char* NextSceneName = "a";

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = {0};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = {0};

	// �Q�[�����[�v
	while (true) {
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		int nextScene = sceneManager->GetSceneNum() + 1;
		// �X�V����

		//�V�[���`�F���W
		if (keys[KEY_INPUT_SPACE] == 1 &&
			oldkeys[KEY_INPUT_SPACE] == 0   ) {
			//���̃V�[������
			sceneManager->ChangeScene(nextScene);
		}

		//�w�i�F�ύX
		if (sceneManager->GetSceneNum() == SceneNum::Title_) {
			color_ = 0xAA5050;
			nowSceneName = "TitleScene";
			NextSceneName = "NewGameScene";
		}
		else if (sceneManager->GetSceneNum() == SceneNum::NewGame_) {
			color_ = 0x50AA50;
			nowSceneName = "NewGameScene";
			NextSceneName = "GamePlayScene";
		}
		else if (sceneManager->GetSceneNum() == SceneNum::GamePlay_) {
			color_ = 0x5050AA;
			nowSceneName = "GamePlayScene";
			NextSceneName = "GameClearScene";
		}
		else if (sceneManager->GetSceneNum() == SceneNum::GameClear_) {
			color_ = 0xAA50AA;
			nowSceneName = "GameClearScene";
			NextSceneName = "TitleScene";
		}

		// �`�揈��
		//�w�i
		DrawBox(0, 0, WIN_WIDTH, WIN_HEIGHT, color_, true);

		DrawFormatString(100, 100, 0xffffff,
			"SceneNum : %d",
			sceneManager->GetSceneNum());
		DrawFormatString(100, 120, 0xffffff,
			"Press SPACE");

		//���݂Ǝ��̃V�[����\��
		DrawFormatString(0, 0, 0xffffff,
			"NowScene  : ");
		DrawFormatString(0, 20, 0xffffff,
			"NextScene : ");
		DrawString(100, 0, nowSceneName, 0xffffff);
		DrawString(100, 20, NextSceneName, 0xffffff);

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
