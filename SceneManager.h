#pragma once

enum SceneNum {
	Title_,
	NewGame_,
	GamePlay_,
	GameClear_
};

class SceneManager final
{
public:
	//コピーコンストラクタを無効にする
	SceneManager(const SceneManager& obj) = delete;
	//代入演算子を無効にする
	SceneManager& operator=(const SceneManager& obj) = delete;

	static SceneManager* GetInstance();

	void ChangeScene(int sceneNo);
	int GetSceneNum() { return sceneNum; }
private:
	SceneManager();
	~SceneManager();

	int sceneNum;
};

