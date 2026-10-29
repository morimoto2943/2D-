#include "DxLib.h"
#include "GameOverScene.h"
#include "../../Input/Input.h"
#include "../../Scene/SceneManager.h"

// 背景のスクロール速度
#define BACK_GROUND_SPEED (-5.0f)

// 自動遷移までの待機時間
#define WAIT_TIMER		(300)

// 待機時間タイマー
int g_WaitTimer = 0;
// GameOver文字画像ハンドル
int g_GameOverHandle = 0;

void InitGameOverScene()
{

	// タイマー初期化
	g_WaitTimer = 0;
}

void LoadGameOverScene()
{

	// GameOver文字画像
	g_GameOverHandle = LoadGraph("Data/GameOver/GameOver.png");
}

void StartGameOverScene()
{
	// 待機タイマーをセット
	g_WaitTimer = WAIT_TIMER;


}

void StepGameOverScene()
{
	
	// タイマーをカウントダウン
	g_WaitTimer--;
}

void UpdateGameOverScene()
{

	// タイマーが0もしくはZキーでタイトルに戻る
	if (g_WaitTimer <= 0 || IsTriggerKey(KEY_Z))
	{
		ChangeScene(SCENE_TITLE);
	}
}

void DrawGameOverScene()
{

	// GameOver文字画像描画
	DrawGraph(500, 350, g_GameOverHandle, TRUE);
}

void FinGameOverScene()
{

	// 文字画像削除
	DeleteGraph(g_GameOverHandle);

}
