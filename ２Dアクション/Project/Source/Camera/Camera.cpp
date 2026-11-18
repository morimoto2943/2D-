#include "DxLib.h"
#include "Camera.h"
#include "../Input/Input.h"
#include "../player/player.h"

#define DEBUG_CAMERA_SPEED (4.0f)
#define CAMERA_SCROLL_START_X (200.f)

CameraData g_CameraData = { 0 };

void InitCamera()
{
}

void StepCamera()
{
	// プレイヤーのデータを取得
	PlayerData* player = GetPlayer();

	// プレイヤーのX座標を基準にカメラのX座標を追従させる
	// （※画面の左端から一定の位置（CAMERA_SCROLL_START_X）を超えたらカメラが動くようにする場合の例です）

	// シンプルにプレイヤーを画面の一定位置に置く追従の例：
	// プレイヤーのX座標 - 画面上の固定位置（例: 200px）をカメラの座標にする
	g_CameraData.posX = player->body.pos.x - CAMERA_SCROLL_START_X;

	// もしカメラがマイナス（画面の左端より外）に行かないように制限したい場合は以下も有効です
	if (g_CameraData.posX < 0.0f)
	{
		g_CameraData.posX = 0.0f;
	}
}

void DrawCamera()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "カメラ= [%f, %f]", g_CameraData.posX, g_CameraData.posY);
}

CameraData GetCamera()
{
	return g_CameraData;
}