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
	//ゲームクリア画面よりも大きい数値を入れられたら
	if (sceneNum > SceneNum::GameClear_) {
		//タイトルに戻る
		sceneNum = SceneNum::Title_;
	}
}

SceneManager::SceneManager()
{
	sceneNum = SceneNum::Title_;
}
