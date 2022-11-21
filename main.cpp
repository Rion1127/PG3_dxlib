#include "DxLib.h"
#include "SceneManager.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LE2A_スズキ_リオン";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 400;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	SceneManager* sceneManager = SceneManager::GetInstance();

	int color_ = 0xffffff;

	const char* nowSceneName = "a";
	const char* NextSceneName = "a";

	// 最新のキーボード情報用
	char keys[256] = {0};

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = {0};

	// ゲームループ
	while (true) {
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		int nextScene = sceneManager->GetSceneNum() + 1;
		// 更新処理

		//シーンチェンジ
		if (keys[KEY_INPUT_SPACE] == 1 &&
			oldkeys[KEY_INPUT_SPACE] == 0   ) {
			//次のシーンを代入
			sceneManager->ChangeScene(nextScene);
		}

		//背景色変更
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

		// 描画処理
		//背景
		DrawBox(0, 0, WIN_WIDTH, WIN_HEIGHT, color_, true);

		DrawFormatString(100, 100, 0xffffff,
			"SceneNum : %d",
			sceneManager->GetSceneNum());
		DrawFormatString(100, 120, 0xffffff,
			"Press SPACE");

		//現在と次のシーンを表示
		DrawFormatString(0, 0, 0xffffff,
			"NowScene  : ");
		DrawFormatString(0, 20, 0xffffff,
			"NextScene : ");
		DrawString(100, 0, nowSceneName, 0xffffff);
		DrawString(100, 20, NextSceneName, 0xffffff);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
