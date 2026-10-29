#include "DxLib.h"
#include "GameClearScene.h"
#include "../../Input/Input.h"
#include "../../Scene/SceneManager.h"
#include <stdio.h>

// 背景のスクロール速度
#define BACK_GROUND_SPEED (-1.5)

// GameClear文字画像
int g_GameClearHandle = 0;

void InitGameClearScene()
{

	// 文字画像ハンドル初期化
	g_GameClearHandle = 0;
}

void LoadGameClearScene()
{

	// GameClear文字画像
	g_GameClearHandle = LoadGraph("Data/GameClear/GameClear.png");
}

void StartGameClearScene()
{
}

void StepGameClearScene()
{

	// Zキーでタイトルに戻る
	if (IsTriggerKey(KEY_Z))
	{
		ChangeScene(SCENE_TITLE);
	}
}

void UpdateGameClearScene()
{
	
}

void DrawGameClearScene()
{


	// 文字画像描画
	DrawGraph(560, 110, g_GameClearHandle, TRUE);

}

void FinGameClearScene()
{

	// 文字画像削除
	DeleteGraph(g_GameClearHandle);

}
