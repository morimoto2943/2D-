#include "DxLib.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/MapManager.h"
#include "../../Camera/Camera.h"
#include "../../player/player.h"

// 背景のスピード
#define BACK_GROUND_SPEED (-1.5f)

void InitPlayScene()
{
	// マップ初期化
	InitMap();

	//カメラの初期化
	InitCamera();

	//プレイヤーの初期化
	InitPlayer();
}

void LoadPlayScene()
{
	LoadPlayer();

	// マップをロード
	LoadMap();
}

void StartPlayScene()
{
	StartPlayer();

	// マップを開始
	StartMap();
}

void StepPlayScene()
{
	// もし StepMap が存在しない場合はここも削除してください
	// StepMap();

	StepPlayer();

	StepCamera();
}

void UpdatePlayScene()
{
	// ? UpdateMap() は存在しないため削除しました

	// プレイヤーの更新
	UpdatePlayer();
}

void DrawPlayScene()
{
	// マップ描画
	DrawMap();

	//カメラの描画
	DrawCamera();

	//プレイヤーの描画
	DrawPlayer();
}

void FinPlayScene()
{
	// マップ終了
	FinMap();

	//プレイヤーの終了
	FinPlayer();
}
