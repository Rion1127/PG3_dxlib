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
	//�R�s�[�R���X�g���N�^�𖳌��ɂ���
	SceneManager(const SceneManager& obj) = delete;
	//������Z�q�𖳌��ɂ���
	SceneManager& operator=(const SceneManager& obj) = delete;

	static SceneManager* GetInstance();

	void ChangeScene(int sceneNo);
	int GetSceneNum() { return sceneNum; }
private:
	SceneManager();
	~SceneManager();

	int sceneNum;
};

