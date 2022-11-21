#include "SceneManager.h"

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;

	return &instance;
}

void SceneManager::ChangeScene(int sceneNo)
{
	sceneNum = sceneNo;
	//�Q�[���N���A��ʂ����傫�����l������ꂽ��
	if (sceneNum > SceneNum::GameClear_) {
		//�^�C�g���ɖ߂�
		sceneNum = SceneNum::Title_;
	}
}

SceneManager::SceneManager()
{
	sceneNum = SceneNum::Title_;
}
