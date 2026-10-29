#pragma once

//プレイヤー設定関連
#define PLAYER_DEFAULT_POS_X (50.0f)
#define PLAYER_DEFAULT_POS_Y (600.0f)
#define PLAYER_MOVE_SPEED (100.0f)

//プレイヤーサイズ
#define PLAYER_WIDTH (1)
#define PLAYER_HEIGHT (1)

// プレイヤーデータ
struct PlayerData
{
	int handle;                                 //画像ハンドル
	bool active;								// 生存フラグ
	bool isTurn;								// 左を向いているか
	bool isAir;									// 空中にいるか
	float posX;									// X座標
	float posY;									// Y座標
	float moveX;								// X移動量
	float moveY;								// Y移動量
	bool hitFlg;                                //ヒットフラグ
};

// 関数のプロトタイプ宣言
void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// 取得関数
PlayerData* GetPlayer();
